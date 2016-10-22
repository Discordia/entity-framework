#pragma once

#include "EntityConfiguration.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual shared_ptr<ComponentFamily> getComponentFamily() = 0;

    virtual void onAddedToEngine(EntityEngine& engine) {}
    virtual void onRemovedFromEngine(EntityEngine& engine) {}
    virtual void update(vector_ptr<entity_ptr> entities, float deltaTime) {}
};
