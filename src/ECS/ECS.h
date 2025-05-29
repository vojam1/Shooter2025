//
// Created by sputnik on 5/18/25.
//

#ifndef ECS_H
#define ECS_H

#include "../Common.h"
#include <bitset>
#include <vector>
#include <array>
#include <deque>
#include <unordered_map>
#include <typeindex>
#include <set>

constexpr uint8_t MAX_COMPONENTS = 32;
typedef std::bitset<MAX_COMPONENTS> Signature;

class Entity {
friend class EntityManager;
public:
    [[nodiscard]] int32_t getId() const { return id; }
    void kill() const;

    bool operator==(const Entity& other) const { return id == other.id; }
    bool operator!=(const Entity& other) const { return id != other.id; }
    bool operator<(const Entity& other) const { return id < other.id; }
    bool operator>(const Entity& other) const { return id > other.id; }

    template<typename TComponent, typename ...TArgs> void addComponent(TArgs&& ...args);
    template<typename TComponent> void removeComponent() const;
    template<typename TComponent> TComponent& getComponent() const;
    template<typename TComponent> [[nodiscard]] bool hasComponent() const;

    Entity(const Entity&) = default;
    Entity& operator=(const Entity&) = default;

    void tag(const std::string& tag) const;
    [[nodiscard]] bool hasTag(const std::string& tag) const;

    void group(const std::string& group) const;
    [[nodiscard]] bool hasGroup(const std::string& group) const;

    class EntityManager* entityManager{};

private:
    explicit Entity(const int32_t id): id(id) {};
    int32_t id;
};

struct IComponent {
    static int32_t nextId;
};

template <typename T>
class Component : public IComponent {
public:
    static int32_t getId(){
        static int32_t id = nextId++;
        return id;
    }
};

class System {
public:
    System() = default;
    ~System() = default;

    void addEntityToSystem(Entity entity);
    void removeEntityFromSystem(Entity entity);

    [[nodiscard]] const std::vector<Entity>& getSystemEntities() const;
    [[nodiscard]] const Signature& getSignature() const;

    template<typename TComponent> void requireComponent();
private:
    std::vector<Entity> entities;
    Signature componentSignature;
};

// System template function definitions ---------------------------------------
template<typename TComponent>
void System::requireComponent() {
    const int32_t componentId = Component<TComponent>::getId();
    componentSignature.set(componentId);
}
// -----------------------------------------------------------------------------

class IPool {
public:
    virtual ~IPool() = default;
};

template<typename T>
class Pool final : public IPool {
public:
    explicit Pool(uint32_t size = 100) {
        data.resize(size);
    }

    ~Pool() override = default;

    [[nodiscard]] bool isEmpty() const { return data.empty(); }
    [[nodiscard]] int32_t getSize() const { return data.size(); }

    void resize(uint32_t size) {
        data.resize(size);
    }
    void clear() {
        data.clear();
    }
    void add(T object) {
        data.push_back(object);
    }
    void set(uint32_t index, T object) {
        data[index] = object;
    }
    T& get(uint32_t index) {
        return data[index];
    }
    T& operator[](uint32_t index) {
        return data[index];
    }

private:
    std::vector<T> data;
};

class EntityManager {
public:
    EntityManager() = default;
    ~EntityManager() = default;

    void update();

    Entity createEntity();
    void killEntity(Entity entity);

    Entity& getEntityFromTag(const std::string &tag);
    void tagEntity(Entity entity, const std::string& tag);
    bool hasTag(Entity entity, const std::string& tag) const;

    void groupEntity(Entity entity, const std::string& group);
    bool hasGroup(Entity entity, const std::string& group) const;
    std::vector<Entity>& getEntitiesInGroup(const std::string& group);
    void removeEntityFromGroup(Entity entity, const std::string& group);
    void removeEntityFromGroups(Entity entity);

    template<typename TComponent, typename ...TArgs> void addComponent(Entity entity, TArgs&& ...args);
    template<typename TComponent> void removeComponent(Entity entity);
    template<typename TComponent> TComponent& getComponent(Entity entity) const;
    template<typename TComponent> bool hasComponent(Entity entity) const;

    template<typename TSystem, typename ...TArgs> void addSystem(TArgs&& ...args);
    template<typename TSystem> void removeSystem();
    template<typename TSystem> TSystem& getSystem() const;
    template<typename TSystem> bool hasSystem() const;

    void addEntityToSystems(Entity entity) const;
    void removeEntityFromSystems(Entity entity);

    uint32_t getNumEntities() const { return numEntities; }
private:
    uint32_t numEntities = 0;
    std::array<Ref<IPool>, MAX_COMPONENTS> componentPools;
    std::vector<Signature> entityComponentSignatures;

    std::unordered_map<std::string, Ref<Entity>> entityPerTag;
    std::unordered_map<std::string, std::vector<Entity>> entitiesInGroup;
    std::vector<std::string> groups;

    std::unordered_map<std::type_index, Ref<System>> systems;

    std::set<Entity> entitiesToBeAdded;
    std::set<Entity> entitiesToBeRemoved;

    std::deque<int32_t> freeIds;
};

// EntityManager template function definitions -----------------------------------------

template<typename TComponent, typename... TArgs>
void EntityManager::addComponent(const Entity entity, TArgs &&... args) {
    const int32_t componentId = Component<TComponent>::getId();
    const int32_t entityId = entity.getId();

    if (!componentPools[componentId]) {
        auto newComponentPool = std::make_shared<Pool<TComponent>>();
        componentPools[componentId] = newComponentPool;
    }

    Ref<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);

    if (entityId >= componentPool->getSize()) {
        componentPool->resize(numEntities);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);
    componentPool->set(entityId, newComponent);
    entityComponentSignatures[entityId].set(componentId);
}

template<typename TComponent>
void EntityManager::removeComponent(const Entity entity){
    const int32_t entityId = entity.getId();
    const int32_t componentId = Component<TComponent>::getId();
    entityComponentSignatures[entityId].set(componentId, false);
}

template<typename TComponent>
TComponent& EntityManager::getComponent(const Entity entity) const{
    const int32_t entityId = entity.getId();
    const int32_t componentId = Component<TComponent>::getId();
    Ref<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(componentPools[componentId]);
    return componentPool->get(entityId);
}

template<typename TComponent>
bool EntityManager::hasComponent(const Entity entity) const{
    const int32_t entityId = entity.getId();
    const int32_t componentId = Component<TComponent>::getId();
    return entityComponentSignatures[entityId].test(componentId);
}

template<typename TSystem, typename ...TArgs>
void EntityManager::addSystem(TArgs&& ...args) {
    Ref<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void EntityManager::removeSystem() {
    Ref<TSystem> system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template<typename TSystem>
TSystem& EntityManager::getSystem() const {
    const auto system = systems.find(std::type_index(typeid(TSystem)));
    return *(std::static_pointer_cast<TSystem>(system->second));
}

template<typename TSystem>
bool EntityManager::hasSystem() const {
    return systems.contains(std::type_index(typeid(TSystem)));
}
//--------------------------------------------------------------------------------------

// Entity template function definitions -------------------------------------------------
template<typename TComponent, typename ...TArgs>
void Entity::addComponent(TArgs&& ...args) {
    entityManager->addComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template<typename TComponent>
void Entity::removeComponent() const {
    entityManager->removeComponent<TComponent>(*this);
}

template<typename TComponent>
TComponent& Entity::getComponent() const{
    return entityManager->getComponent<TComponent>(*this);
}

template<typename TComponent>
bool Entity::hasComponent() const{
    return entityManager->hasComponent<TComponent>(*this);
}
// --------------------------------------------------------------------------------------

#endif //ECS_H
