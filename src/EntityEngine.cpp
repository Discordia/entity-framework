//
// Created by roberts on 2015-10-06.
//

#include "EntityEngine.h"
#include "EntitySystem.h"
#include "EntityOperation.h"

#include <algorithm>

int EntityEngine::entityUUIDs = 0;

EntityEngine::EntityEngine()
        : updating(false)
{
    componentOperationHandler = shared_ptr<ComponentOperationHandler>(new ComponentOperationHandler(this));
}

EntityEngine::~EntityEngine()
{
}

void EntityEngine::addSystem(shared_ptr<EntitySystem> entitySystem)
{
    entitySystem->addedToEngine(shared_from_this());
    systems.push_back(entitySystem);
}

void EntityEngine::removeSystem(shared_ptr<EntitySystem> entitySystem)
{
    systems.erase(std::remove(systems.begin(), systems.end(), entitySystem), systems.end());
    entitySystem->removedFromEngine(shared_from_this());
}

void EntityEngine::addEntity(shared_ptr<Entity> entity)
{
    if (entity->getUUID() != 0)
    {
        // TODO: handle error
        return;
    }

    entity->setUUID(entityUUIDs++);

    shared_ptr<EntityOperation> entityOperation = shared_ptr<EntityOperation>(
            new EntityOperation(entity, EntityOperation::EntityOperationType::ADD));
    entityOperations.push_back(entityOperation);
}

void EntityEngine::removeEntity(shared_ptr<Entity> entity)
{
    shared_ptr<EntityOperation> entityOperation = shared_ptr<EntityOperation>(
            new EntityOperation(entity, EntityOperation::EntityOperationType::REMOVE));
    entityOperations.push_back(entityOperation);
}

const shared_ptr<vector<shared_ptr<Entity>>> EntityEngine::getEntitiesFor(ComponentFamily& componentFamily)
{
    auto keyValueIt = componentFamilies.find(componentFamily);

    if (keyValueIt != componentFamilies.end())
    {
        return keyValueIt->second;
    }

    shared_ptr<vector<shared_ptr<Entity>>> familyEntities(new vector<shared_ptr<Entity>>());
    std::pair<ComponentFamily, shared_ptr<vector<shared_ptr<Entity>>>> keyValue(componentFamily, familyEntities);
    componentFamilies.insert(keyValue);

    for (auto entity : entities)
    {
        // TODO: optimization - Only interested in the new family
        updateFamilyMembership(entity);
    }

    return familyEntities;
}

void EntityEngine::update(float deltaTime)
{
    refresh();

    if (updating)
    {
        // TODO: handle error
        return;
    }

    updating = true;
    for (auto system : systems)
    {
        system->update(deltaTime);

        refresh();
    }

    updating = false;
}

void EntityEngine::refresh()
{
    processPendingComponentOperations();
    processPendingEntityOperations();
}

void EntityEngine::addComponentOperation(shared_ptr<ComponentOperation> componentOperation)
{
    componentOperations.push_back(componentOperation);
}

void EntityEngine::addEntityInternal(shared_ptr<Entity> entity)
{
    entity->componentOperationHandler = this->componentOperationHandler;
    entities.push_back(entity);
}

void EntityEngine::removeEntityInternal(shared_ptr<Entity> entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

void EntityEngine::processPendingComponentOperations()
{
    for (auto componentOperation : componentOperations)
    {
        auto entity = componentOperation->entity;
        auto component = componentOperation->component;
        
        switch (componentOperation->type) 
        {
            case ComponentOperation::ADD:
                entity->addInternal(component);    
                break;
            
            case ComponentOperation::REMOVE:
                entity->removeInternal(component);
                break;
        }
    }

    componentOperations.clear();
}

void EntityEngine::processPendingEntityOperations()
{
    for (auto entityOperation : entityOperations)
    {
        auto entity = entityOperation->entity;
        
        switch (entityOperation->type)
        {
            case EntityOperation::ADD:
                addEntityInternal(entity);
                break;

            case EntityOperation::REMOVE:
                removeEntityInternal(entity);
                break;
        }
    }

    entityOperations.clear();
}

void EntityEngine::updateFamilyMembership(shared_ptr<Entity> entity)
{
    bool removing = false;
    bitset<32>& familyBits = entity->getFamilyBits();
    
    for (auto entry : componentFamilies)
    {
        ComponentFamily family =  entry.first;
        int familyIndex = family.getIndex();

        // TODO: get rid of cast
        bool belongsToFamily = familyBits.test(static_cast<size_t>(familyIndex));
        bool matches = family.matches(entity) && !removing;

        if (belongsToFamily != matches) {
            auto familyEntities = entry.second;
            
            if (matches) {
                familyEntities->push_back(entity);
                familyBits.set(static_cast<size_t>(familyIndex));
            } else {
                familyEntities->erase(std::remove(familyEntities->begin(), familyEntities->end(), entity), familyEntities->end());
                familyBits.reset(static_cast<size_t>(familyIndex));
            }
        }
    }
}
