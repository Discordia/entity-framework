#include "EntityEngine.h"

ComponentOperation::ComponentOperation(ComponentOperation::ComponentOperationType type, shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId)
        : type(type), entity(entity), component(component), componentId(componentId)
{
}

shared_ptr<ComponentOperation> ComponentOperation::createAdd(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId)
{
    return shared_ptr<ComponentOperation>(new ComponentOperation(ComponentOperationType::ADD, entity, component, componentId));
}

shared_ptr<ComponentOperation> ComponentOperation::createRemove(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId)
{
    return shared_ptr<ComponentOperation>(new ComponentOperation(ComponentOperationType::REMOVE, entity, component, componentId));
}

ComponentOperationHandler::ComponentOperationHandler(EntityEngine& engine)
        : engine(engine)
{
}

void ComponentOperationHandler::add(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId)
{
    engine.addComponentOperation(ComponentOperation::createAdd(entity, component, componentId));
}

void ComponentOperationHandler::remove(shared_ptr<Entity> entity, shared_ptr<Component> component, TypeId componentId)
{
    engine.addComponentOperation(ComponentOperation::createRemove(entity, component, componentId));
}
