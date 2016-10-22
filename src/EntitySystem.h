#pragma once

#include "EntityConfiguration.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual void onAddedToEngine(shared_ptr<EntityEngine> engine) {}
    virtual void onRemovedFromEngine(shared_ptr<EntityEngine> engine) {}
    virtual void update(float deltaTime) {}
};
