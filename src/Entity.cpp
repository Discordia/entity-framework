#include "Entity.h"

Entity::Entity()
    : uuid(0)
{
}

int Entity::getUUID()
{
    return uuid;
}

bitset<32>& Entity::getComponentBits()
{
    return componentBits;
}

bitset<32>& Entity::getFamilyBits()
{
    return familyBits;
}

void Entity::setUUID(int uuid)
{
    this->uuid = uuid;
}

void Entity::addInternal(shared_ptr<Component> component, TypeId componentId)
{
    if (componentId >= components.size())
    {
        components.resize(static_cast<size_t>(componentId + 1), nullptr);
    }

    if (components[componentId] != nullptr)
    {
        removeInternal(componentId);
    }

    components[componentId] = component;
    componentBits.set(componentId);
}

void Entity::removeInternal(TypeId componentId)
{
    if (components[componentId] == nullptr)
    {
        return;
    }

    components[componentId] = nullptr;
    componentBits.reset(componentId);
}
