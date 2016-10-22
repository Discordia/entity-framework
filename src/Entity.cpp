#include "Entity.h"

Entity::Entity()
{
    resetUUID();
}

Entity::Entity(int32_t uuid, shared_ptr<ComponentOperationHandler> componentOperationHandler)
    : uuid(uuid), componentOperationHandler(componentOperationHandler)
{
}

int32_t Entity::getUUID()
{
    return uuid;
}

ComponentBitSet& Entity::getComponentBits()
{
    return componentBits;
}

ComponentBitSet& Entity::getFamilyBits()
{
    return familyBits;
}

void Entity::setUUID(int32_t uuid)
{
    this->uuid = uuid;
}

void Entity::resetUUID()
{
    this->uuid = -1;
}

void Entity::addInternal(shared_ptr<Component> component, TypeId componentId)
{
    components[componentId] = component;
    componentBits.set(componentId);
}

void Entity::removeInternal(TypeId componentId)
{
    components[componentId] = nullptr;
    componentBits.reset(componentId);
}
