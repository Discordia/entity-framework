//
// Created by roberts on 2015-10-08.
//

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

    ComponentOperation(Entity* entity, shared_ptr<Component> component, ComponentOperationType type);

    static shared_ptr<ComponentOperation> createAdd(Entity* entity, shared_ptr<Component> component);
    static shared_ptr<ComponentOperation> createRemove(Entity* entity, shared_ptr<Component> component);

public:
    Entity* entity;
    shared_ptr<Component> component;
    ComponentOperationType type;
};

class ComponentOperationHandler
{
public:
    ComponentOperationHandler(EntityEngine* engine);

    void add(Entity* entity, shared_ptr<Component> component);
    void remove(Entity* entity, shared_ptr<Component> component);

private:
    EntityEngine* engine;
};


#endif //ENTITY_FRAMEWORK_COMPONENTOPERATIONHANDLER_H
