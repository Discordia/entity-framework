#include "Entity.h"

Entity::Entity()
    : uuid(0)
{
}

int Entity::getUUID()
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

void Entity::setUUID(int uuid)
{
    this->uuid = uuid;
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
