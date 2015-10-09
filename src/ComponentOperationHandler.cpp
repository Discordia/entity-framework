//
// Created by roberts on 2015-10-08.
//

#include "EntityEngine.h"
#include "ComponentOperationHandler.h"

ComponentOperation::ComponentOperation(Entity* entity, shared_ptr<Component> component, ComponentOperation::ComponentOperationType type)
        : entity(entity), component(component), type(type)
{
}

shared_ptr<ComponentOperation> ComponentOperation::createAdd(Entity* entity, shared_ptr<Component> component)
{
    return shared_ptr<ComponentOperation>(new ComponentOperation(entity, component, ComponentOperationType::ADD));
}

shared_ptr<ComponentOperation> ComponentOperation::createRemove(Entity* entity, shared_ptr<Component> component)
{
    return shared_ptr<ComponentOperation>(new ComponentOperation(entity, component, ComponentOperationType::REMOVE));
}

ComponentOperationHandler::ComponentOperationHandler(EntityEngine* engine)
        : engine(engine)
{
}

void ComponentOperationHandler::add(Entity* entity, shared_ptr<Component> component)
{
    engine->addComponentOperation(ComponentOperation::createAdd(entity, component));
}

void ComponentOperationHandler::remove(Entity* entity, shared_ptr<Component> component)
{
    engine->addComponentOperation(ComponentOperation::createRemove(entity, component));
}
