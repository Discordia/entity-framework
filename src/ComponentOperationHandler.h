#pragma once

#include <memory>

using std::shared_ptr;

class Entity;
class EntityEngine;

class ComponentOperation
{
public:
    enum ComponentOperationType
    {
        ADD,
        REMOVE
    };

    ComponentOperation(ComponentOperationType type, shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId);

    static shared_ptr<ComponentOperation> createAdd(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId);
    static shared_ptr<ComponentOperation> createRemove(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId);

public:
    ComponentOperationType type;
    shared_ptr<Entity> entity;
    shared_ptr<Component> component;
    TypeId componentId;
};

class ComponentOperationHandler
{
public:
    ComponentOperationHandler(EntityEngine* engine);

    void add(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId);
    void remove(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId);

private:
    EntityEngine* engine;
};
