#pragma once

#include "EntityConfiguration.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual ComponentFamily& getComponentFamily() = 0;

    virtual void onAddedToEngine(EntityEngine& engine, vector_ptr<entity_ptr> entities) {}
    virtual void onRemovedFromEngine(EntityEngine& engine) {}
    virtual void onEntityAdded(shared_ptr<Entity> entity) {}
    virtual void onEntityRemoved(shared_ptr<Entity> entity) {}
    virtual void update(vector_ptr<entity_ptr> entities, float deltaTime) {}
};
