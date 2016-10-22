#pragma once

#include "Entity.h"
#include "EntityOperation.h"
#include "ComponentOperationHandler.h"
#include "ComponentFamily.h"

class EntitySystem;

template<class T> using  vector_ptr = shared_ptr<vector<T>> ;
typedef shared_ptr<Entity> entity_ptr;

class EntityEngine
{
public :
    EntityEngine();

    void addSystem(shared_ptr<EntitySystem> entitySystem);
    void removeSystem(shared_ptr<EntitySystem> entitySystem);

    shared_ptr<Entity> createEntity();
    void addEntity(shared_ptr<Entity> entity);
    void addEntities(vector_ptr<entity_ptr> entities);
    void removeEntity(shared_ptr<Entity> entity);

    const vector_ptr<entity_ptr> getEntitiesFor(ComponentFamily& componentFamily);

    bool update(float deltaTime);
    void refresh();

private:
    friend void ComponentOperationHandler::add(shared_ptr<Entity>, shared_ptr<Component>, TypeId i);
    friend void ComponentOperationHandler::remove(shared_ptr<Entity>, shared_ptr<Component>, TypeId i);

    void addComponentOperation(shared_ptr<ComponentOperation> componentOperation);

private:
    void addEntityInternal(shared_ptr<Entity> entity);
    void removeEntityInternal(shared_ptr<Entity> entity);
    int32_t nextEntityUUID();

    void processPendingComponentOperations();
    void processPendingEntityOperations();
    void updateFamilyMembership(shared_ptr<Entity> entity, bool removing = false);

private:
    bool updating;
    static int32_t entityUUIDs;
    vector<shared_ptr<Entity>> entities;
    vector<shared_ptr<EntitySystem>> systems;
    vector<shared_ptr<EntityOperation>> entityOperations;
    vector<shared_ptr<ComponentOperation>> componentOperations;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
    unordered_map<ComponentFamily, vector_ptr<entity_ptr>, ComponentFamilyHasher> componentFamilies;
};