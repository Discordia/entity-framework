//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_ENTITYENGINE_H
#define ENTITY_FRAMEWORK_ENTITYENGINE_H

#include <memory>
#include <vector>
#include "Entity.h"
#include "EntityOperation.h"
#include "ComponentOperationHandler.h"

using std::shared_ptr;
using std::vector;

class EntitySystem;

class EntityEngine
{
public :
    EntityEngine();
    ~EntityEngine();

    void addSystem(shared_ptr<EntitySystem> entitySystem);

    void addEntity(shared_ptr<Entity> entity);
    void removeEntity(shared_ptr<Entity> entity);

    void update(float deltaTime);
    void refresh();

private:
    friend void ComponentOperationHandler::add(Entity*, shared_ptr<Component>);
    friend void ComponentOperationHandler::remove(Entity*, shared_ptr<Component>);

    void addComponentOperation(shared_ptr<ComponentOperation> componentOperation);

private:
    void addEntityInternal(shared_ptr<Entity> entity);
    void removeEntityInternal(shared_ptr<Entity> entity);

    void processPendingComponentOperations();
    void processPendingEntityOperations();

private:
    bool updating;
    static int entityUUIDs;
    vector<shared_ptr<EntitySystem>> systems;
    vector<shared_ptr<EntityOperation>> entityOperations;
    vector<shared_ptr<ComponentOperation>> componentOperations;
    vector<shared_ptr<Entity>> entities;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
};


#endif //ENTITY_FRAMEWORK_ENTITYENGINE_H
