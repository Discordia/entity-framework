#pragma once

#include <memory>

using std::shared_ptr;

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual void addedToEngine(shared_ptr<EntityEngine> engine) {}
    virtual void removedFromEngine(shared_ptr<EntityEngine> engine) {}
    virtual void update(float deltaTime) {}
};
