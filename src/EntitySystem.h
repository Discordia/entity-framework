#pragma once

#include "EntityConfiguration.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual void addedToEngine(shared_ptr<EntityEngine> engine) {}
    virtual void removedFromEngine(shared_ptr<EntityEngine> engine) {}
    virtual void update(float deltaTime) {}
};
