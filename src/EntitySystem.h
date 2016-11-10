#pragma once

#include "ClassTypeId.h"

class EntityEngine;

class EntitySystem
{
public:
    virtual ~EntitySystem() {}

    virtual const TypeId getTypeId() = 0;
    virtual ComponentFamily& getComponentFamily() = 0;

    virtual void onAddedToEngine(EntityEngine& engine) {}
    virtual void onRemovedFromEngine(EntityEngine& engine) {}
    virtual void onEntityAdded(shared_ptr<Entity> entity) {}
    virtual void onEntityRemoved(shared_ptr<Entity> entity) {}
    virtual void update(vector_ptr<shared_ptr<Entity>> entities, float deltaTime) {}
};

template<class T>
const TypeId getEntitySystemTypeId()
{
    return ClassTypeId<EntitySystem>::getTypeId<T>();
}

template<class T>
struct EntitySystemPredicate
{
    template<class U>
    bool operator()(U value)
    {
        TypeId typeIdT = getEntitySystemTypeId<T>();
        TypeId typeIdU = value.first->getTypeId();
        return typeIdT == typeIdU;
    }
};
