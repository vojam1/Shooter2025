//
// Created by sputnik on 5/18/25.
//

#include "ECS.h"

#include <algorithm>
#include <ranges>

void Entity::tag(const std::string &tag) const {
    entityManager->tagEntity(*this, tag);
}

bool Entity::hasTag(const std::string &tag) const {
    return entityManager->hasTag(*this, tag);
}

void Entity::kill() const {
    entityManager->killEntity(*this);
}

int32_t IComponent::nextId = 0;

void System::addEntityToSystem(const Entity entity) {
    entities.push_back(entity);
}

void System::removeEntityFromSystem(Entity entity) {
    std::erase_if(entities,[&entity](const Entity& other) {
        return other == entity;
    });
}

const std::vector<Entity>& System::getSystemEntities() const {
    return entities;
}

const Signature& System::getSignature() const {
    return componentSignature;
}

void EntityManager::update() {
    for (const Entity entity: entitiesToBeAdded) {
        addEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for (const Entity entity: entitiesToBeRemoved) {
        const int32_t entityId = entity.getId();

        removeEntityFromSystems(entity);
        entityComponentSignatures[entityId].reset();
        freeIds.push_back(entityId);
    }
    entitiesToBeRemoved.clear();
}

Entity EntityManager::createEntity() {
    int32_t entityId;

    if (!freeIds.empty()) {
        entityId = freeIds.front();
        freeIds.pop_front();
    } else {
        entityId = static_cast<int>(numEntities++);
        if (entityId >= entityComponentSignatures.size()) {
            entityComponentSignatures.resize(entityId + 1);
        }
    }

    Entity entity(entityId);
    entity.entityManager = this;
    entitiesToBeAdded.insert(entity);

    return entity;
}

void EntityManager::killEntity(const Entity entity) {
    entitiesToBeRemoved.insert(entity);
}

void EntityManager::addEntityToSystems(const Entity entity) const {
    const int32_t entityId = entity.getId();
    const Signature entitySignature = entityComponentSignatures[entityId];
    for (const auto &system: systems | std::views::values) {
        const Signature& systemSignature = system->getSignature();

        if ((entitySignature & systemSignature) == systemSignature) {
            system->addEntityToSystem(entity);
        }
    }

}

void EntityManager::removeEntityFromSystems(const Entity entity) {
    for (const auto &system: systems | std::views::values) {
        system->removeEntityFromSystem(entity);
    }
}

void EntityManager::tagEntity(const Entity entity, const std::string &tag) {
    const auto entityId = entity.getId();
    tagPerEntity.insert(std::make_pair(entityId, tag));
}

bool EntityManager::hasTag(const Entity entity, const std::string &tag) const {
    const auto entityId = entity.getId();
    return tagPerEntity.at(entityId) == tag;
}
