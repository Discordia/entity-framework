#include "EntityEngine.h"
#include "EntitySystem.h"

int32_t EntityEngine::entityUUIDs = 0;

EntityEngine::EntityEngine()
        : updating(false)
{
    componentOperationHandler = shared_ptr<ComponentOperationHandler>(new ComponentOperationHandler(*this));
}

shared_ptr<Entity> EntityEngine::createEntity()
{
    entity_ptr entity(new Entity(nextEntityUUID(), componentOperationHandler));
    auto operation = shared_ptr<EntityOperation>(new EntityOperation(entity, EntityOperation::EntityOperationType::ADD));
    entityOperations.push_back(operation);

    return entity;
}

void EntityEngine::addEntity(shared_ptr<Entity> entity)
{
    if (entity->getUUID() != -1)
    {
        return;
    }

    entity->setUUID(nextEntityUUID());

    auto operation = shared_ptr<EntityOperation>(new EntityOperation(entity, EntityOperation::EntityOperationType::ADD));
    entityOperations.push_back(operation);
}

void EntityEngine::addEntities(vector<entity_ptr>& entities)
{
    for (auto entity : entities)
    {
        addEntity(entity);
    }
}

void EntityEngine::removeEntity(shared_ptr<Entity> entity)
{
    auto operation = shared_ptr<EntityOperation>(new EntityOperation(entity, EntityOperation::EntityOperationType::REMOVE));
    entityOperations.push_back(operation);
}

bool EntityEngine::update(float deltaTime)
{
    refresh();

    if (updating)
    {
        return false;
    }

    updating = true;
    for (auto systemPair : systems)
    {
        auto system = systemPair.first;
        auto entities = systemPair.second;
        system->update(entities, deltaTime);
    }

    updating = false;

    return true;
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
    entity->resetUUID();
}

int32_t EntityEngine::nextEntityUUID()
{
    return ++entityUUIDs;
}

void EntityEngine::processPendingComponentOperations()
{
    for (auto componentOperation : componentOperations)
    {
        auto entity = componentOperation->entity;
        auto component = componentOperation->component;
        auto componentId = componentOperation->componentId;

        switch (componentOperation->type)
        {
            case ComponentOperation::ADD:
                entity->addInternal(component, componentId);
                break;

            case ComponentOperation::REMOVE:
                entity->removeInternal(componentId);
                break;
        }

        updateFamilyMembership(entity);
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
                updateFamilyMembership(entity);
                break;

            case EntityOperation::REMOVE:
                removeEntityInternal(entity);
                updateFamilyMembership(entity, true);
                break;
        }
    }

    entityOperations.clear();
}

// TODO: optimization - Only interested in the new family
void EntityEngine::updateFamilyMembershipAll()
{
    for (auto entity : entities)
    {
        updateFamilyMembership(entity);
    }
}

void EntityEngine::updateFamilyMembership(shared_ptr<Entity> entity, bool removing)
{
    auto& familyBits = entity->getFamilyBits();
    
    for (auto entry : systems)
    {
        auto system =  entry.first;
        auto& family = system->getComponentFamily();
        auto familyIndex = family.getIndex();

        bool belongsToFamily = familyBits.test(familyIndex);
        bool matches = family.matches(entity) && !removing;

        if (belongsToFamily != matches) {
            auto familyEntities = entry.second;
            
            if (matches) {
                familyEntities->push_back(entity);
                familyBits.set(familyIndex);
                system->onEntityAdded(entity);
            } else {
                familyEntities->erase(std::remove(familyEntities->begin(), familyEntities->end(), entity), familyEntities->end());
                familyBits.reset(familyIndex);
                system->onEntityRemoved(entity);
            }
        }
    }
}
