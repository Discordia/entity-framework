#pragma once

#include "ClassTypeId.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual const ComponentFamily& getComponentFamily() const = 0;

    virtual void onAddedToEngine(EntityEngine& engine) {}
    virtual void onRemovedFromEngine(EntityEngine& engine) {}
    virtual void onEntityAdded(shared_ptr<Entity> entity) {}
    virtual void onEntityRemoved(shared_ptr<Entity> entity) {}
    virtual void update(vector_ptr<shared_ptr<Entity>> entities, EntityEngine& engine, float deltaTime) {}
};

template<class T>
const TypeId getEntitySystemTypeId()
{
    return ClassTypeId<EntitySystem>::getTypeId<T>();
}

struct EntitySystemPredicate
{
    EntitySystemPredicate(shared_ptr<EntitySystem> system)
        :  system(system)
    {}

    template<class U>
    bool operator()(U value)
    {
        return system == value.first;
    }

private:
    shared_ptr<EntitySystem> system;
};
