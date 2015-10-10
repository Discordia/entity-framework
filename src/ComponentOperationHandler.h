#ifndef ENTITY_FRAMEWORK_COMPONENTOPERATIONHANDLER_H
#define ENTITY_FRAMEWORK_COMPONENTOPERATIONHANDLER_H

class EntityEngine;

class ComponentOperation
{
public:
    enum ComponentOperationType
    {
        ADD,
        REMOVE
    };

    ComponentOperation(shared_ptr<Entity> entity, shared_ptr<Component> component, ComponentOperationType type);

    static shared_ptr<ComponentOperation> createAdd(shared_ptr<Entity> entity, shared_ptr<Component> component);
    static shared_ptr<ComponentOperation> createRemove(shared_ptr<Entity> entity, shared_ptr<Component> component);

public:
    shared_ptr<Entity> entity;
    shared_ptr<Component> component;
    ComponentOperationType type;
};

class ComponentOperationHandler
{
public:
    ComponentOperationHandler(EntityEngine* engine);

    void add(shared_ptr<Entity> entity, shared_ptr<Component> component);
    void remove(shared_ptr<Entity> entity, shared_ptr<Component> component);

private:
    EntityEngine* engine;
};


#endif
