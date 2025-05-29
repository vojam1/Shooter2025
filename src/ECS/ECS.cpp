//
// Created by sputnik on 5/18/25.
//

#include "ECS.h"

#include <algorithm>
#include <ranges>

void Entity::tag(const std::string &tag) const {
    entityManager->tagEntity(*this, tag);
}

void Entity::group(const std::string &group) const {
    entityManager->groupEntity(*this, group);
}


bool Entity::hasTag(const std::string &tag) const {
    return entityManager->hasTag(*this, tag);
}

bool Entity::hasGroup(const std::string &group) const {
    return entityManager->hasGroup(*this, group);
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
    for (const Entity& entity: entitiesToBeAdded) {
        addEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for (const Entity entity: entitiesToBeRemoved) {
        const int32_t entityId = entity.getId();

        removeEntityFromSystems(entity);
        removeEntityFromGroups(entity);
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
    auto ent = std::make_shared<Entity>(entity);
    entityPerTag.insert(std::make_pair(tag, ent));
}

bool EntityManager::hasTag(const Entity entity, const std::string &tag) const {
    return *entityPerTag.at(tag) == entity;
}

Entity &EntityManager::getEntityFromTag(const std::string& tag) {
    return *entityPerTag[tag];
}

void EntityManager::groupEntity(const Entity entity, const std::string &group) {
    if (std::ranges::find(groups, group) == groups.end()) {
        groups.push_back(group);
    }
    if (!entitiesInGroup.contains(group)) {
        entitiesInGroup[group] = std::vector<Entity>();
    }
    entitiesInGroup.at(group).push_back(entity);
}

bool EntityManager::hasGroup(const Entity entity, const std::string &group) const {
    const auto& vector = entitiesInGroup.at(group);
    return std::ranges::find(vector, entity) != vector.end();
}

std::vector<Entity>& EntityManager::getEntitiesInGroup(const std::string &group) {
    return entitiesInGroup[group];
}

void EntityManager::removeEntityFromGroup(Entity entity, const std::string &group) {
    entitiesInGroup.at(group).erase(std::ranges::find(entitiesInGroup.at(group), entity));
}

void EntityManager::removeEntityFromGroups(const Entity entity) {
    for (auto& group: groups) {
        if (entity.hasGroup(group)) {
            removeEntityFromGroup(entity, group);
        }
    }
}