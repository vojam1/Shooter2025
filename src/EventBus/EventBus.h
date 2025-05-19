//
// Created by sputnik on 5/19/25.
//

#ifndef EVENTBUS_H
#define EVENTBUS_H
#include <functional>
#include <map>
#include <typeindex>
#include <list>

#include "Event.h"
#include "../Common.h"

class IEventCallback {
public:
    virtual ~IEventCallback() = default;

    void execute(Event& event) {
        call(event);
    }

private:
    virtual void call(Event& event) = 0;
};

template <typename TOwner, typename TEvent>
class EventCallback final : public IEventCallback {
public:
    typedef void (TOwner::*CallbackFunction)(TEvent&);

    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
        this->ownerInstance = ownerInstance;
        this->callbackFunction = callbackFunction;
    }
    ~EventCallback() override = default;

private:
    TOwner* ownerInstance;
    CallbackFunction callbackFunction;

    void call(Event &event) override {
        std::invoke(this->callbackFunction, static_cast<TOwner*>(this->ownerInstance), static_cast<TEvent&>(event));
    }
};

typedef std::list<UniqueRef<IEventCallback>> HandlerList;

class EventBus {
public:
    EventBus() = default;
    ~EventBus() = default;

    void reset() {
        subscribers.clear();
    }

    template<typename TEvent, typename ... TArgs>
    void emitEvent(TArgs&& ...args) {
        const auto handlers = subscribers[typeid(TEvent)].get();
        if (handlers) {
            for (auto & it : *handlers) {
                auto handler = it.get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->execute(event);
            }
        }
    }

    template<typename TEvent, typename TOwner>
    void subscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }

        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }

private:
    std::map<std::type_index, UniqueRef<HandlerList>> subscribers;
};

#endif //EVENTBUS_H
