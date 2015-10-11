#ifndef ENTITY_FRAMEWORK_ENTITYENGINE_H
#define ENTITY_FRAMEWORK_ENTITYENGINE_H

#include <memory>
#include <vector>
#include <unordered_map>
#include "Entity.h"
#include "EntityOperation.h"
#include "ComponentOperationHandler.h"
#include "ComponentFamily.h"

using std::shared_ptr;
using std::vector;
using std::unordered_map;
using std::enable_shared_from_this;

class EntitySystem;

template<class T> using  vector_ptr = shared_ptr<vector<T>> ;
typedef shared_ptr<Entity> entity_ptr;

class EntityEngine : public enable_shared_from_this<EntityEngine>
{
public :
    EntityEngine();
    ~EntityEngine();

    void addSystem(shared_ptr<EntitySystem> entitySystem);
    void removeSystem(shared_ptr<EntitySystem> entitySystem);

    void addEntity(shared_ptr<Entity> entity);
    void removeEntity(shared_ptr<Entity> entity);

    const shared_ptr<vector<shared_ptr<Entity>>> getEntitiesFor(ComponentFamily& componentFamily);

    bool update(float deltaTime);
    void refresh();

private:
    friend void ComponentOperationHandler::add(shared_ptr<Entity>, shared_ptr<Component>);
    friend void ComponentOperationHandler::remove(shared_ptr<Entity>, shared_ptr<Component>);

    void addComponentOperation(shared_ptr<ComponentOperation> componentOperation);

private:
    void addEntityInternal(shared_ptr<Entity> entity);
    void removeEntityInternal(shared_ptr<Entity> entity);

    void processPendingComponentOperations();
    void processPendingEntityOperations();
    void updateFamilyMembership(shared_ptr<Entity> entity, bool removing = false);

private:
    bool updating;
    static int entityUUIDs;
    vector<shared_ptr<EntitySystem>> systems;
    vector<shared_ptr<EntityOperation>> entityOperations;
    vector<shared_ptr<ComponentOperation>> componentOperations;
    vector<shared_ptr<Entity>> entities;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
    unordered_map<ComponentFamily, vector_ptr<entity_ptr>, ComponentFamilyHasher> componentFamilies;
};


#endif
