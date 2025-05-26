#ifndef EVENTBUS_H
#define EVENTBUS_H

#include "Event.h"
#include <map>
#include <typeindex>
#include <functional>
#include <list>
#include <memory>

class IEventCallback {
    private:
        virtual void Call(Event& e) = 0;

    public:
        virtual ~IEventCallback() = default;
        
        void Execute(Event& e) {
            Call(e);
        }
};

template <typename TOwner, typename TEvent>
class EventCallback: public IEventCallback {
    private:
        typedef void (TOwner::*CallbackFunction)(TEvent&);

        TOwner* ownerInstance;
        CallbackFunction callbackFunction;

        virtual void Call(Event& e) override {
            std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
        }

    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
            this->ownerInstance = ownerInstance;
            this->callbackFunction = callbackFunction;
        }
    
        virtual ~EventCallback() override = default;
};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventBus {
    private:
        std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
    public:
        EventBus() = default;
        
        ~EventBus() = default;

        // Clears the subscribers list
        void Reset() {
            subscribers.clear();
        }

        /////////////////////////////////////////////////////////////////////// 
        // Subscribe to an event type <T>
        // In our implementation, a listener subscribes to an event
        // Example: eventBus->SubscribeToEvent<CollisionEvent>(this, &Game::onCollision);
        /////////////////////////////////////////////////////////////////////// 
        template <typename TEvent, typename TOwner>
        void subscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
            auto it = subscribers.find(typeid(TEvent));
            if (it == subscribers.end()) {
                subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
            }
            auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
            subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
        }

        /////////////////////////////////////////////////////////////////////// 
        // Emit an event of type <T>
        // In our implementation, as soon as something emits an
        // event we go ahead and execute all the listener callback functions
        // Example: eventBus->EmitEvent<CollisionEvent>(player, enemy);
        /////////////////////////////////////////////////////////////////////// 
        template <typename TEvent, typename ...TArgs>
        void emitEvent(TArgs&& ...args) {
            auto it = subscribers.find(typeid(TEvent));
            if (it != subscribers.end()) {
                TEvent event(std::forward<TArgs>(args)...);
                for (auto& handlerPtr : *(it->second)) {
                    handlerPtr->Execute(event);
                }
            }
        }

};

#endif