#pragma once

#include "Entity.h"
#include "EntityOperation.h"
#include "ComponentOperationHandler.h"
#include "ComponentFamily.h"
#include "EntitySystem.h"

using system_entities_pair = pair<shared_ptr<EntitySystem>, vector_ptr<entity_ptr>>;

class EntityEngine
{
public :
    EntityEngine();

    template<class T, class... Args>
    void addSystem(Args&&... args);

    template<class T>
    void removeSystem();

    shared_ptr<Entity> createEntity();
    void addEntity(shared_ptr<Entity> entity);
    void addEntities(vector<entity_ptr>& entities);
    void removeEntity(shared_ptr<Entity> entity);

    bool update(float deltaTime);
    void refresh();

private:
    friend void ComponentOperationHandler::add(shared_ptr<Entity>, shared_ptr<Component>, TypeId typeId);
    friend void ComponentOperationHandler::remove(shared_ptr<Entity>, shared_ptr<Component>, TypeId typeId);

    void addComponentOperation(shared_ptr<ComponentOperation> componentOperation);

private:
    void addEntityInternal(shared_ptr<Entity> entity);
    void removeEntityInternal(shared_ptr<Entity> entity);
    int32_t nextEntityUUID();

    void processPendingComponentOperations();
    void processPendingEntityOperations();
    void updateFamilyMembershipAll();
    void updateFamilyMembership(shared_ptr<Entity> entity, bool removing = false);

private:
    bool updating;
    static int32_t entityUUIDs;
    vector<shared_ptr<Entity>> entities;
    vector<system_entities_pair> systems;
    unordered_map<TypeId, shared_ptr<EntitySystem>> systemsMap;
    vector<shared_ptr<EntityOperation>> entityOperations;
    vector<shared_ptr<ComponentOperation>> componentOperations;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
};

template<class T, class... Args>
void EntityEngine::addSystem(Args&&... args)
{
    auto system = shared_ptr<T>(new T{std::forward<Args>(args)...});

    vector_ptr<entity_ptr> familyEntities(new vector<entity_ptr>());
    systems.push_back(make_pair(system, familyEntities));
    systemsMap[getEntitySystemTypeId<T>()] = system;

    updateFamilyMembershipAll();

    system->onAddedToEngine(*this);
}

template<class T>
void EntityEngine::removeSystem()
{
    auto typeId = getEntitySystemTypeId<T>();
    auto system = systemsMap[typeId];

    systems.erase(remove_if(systems.begin(), systems.end(), EntitySystemPredicate(system)), systems.end());
    systemsMap.erase(typeId);
    
    system->onRemovedFromEngine(*this);
}