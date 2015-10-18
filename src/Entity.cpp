#include "Entity.h"
#include "ComponentOperationHandler.h"

Entity::Entity()
    : uuid(0)
{
}

Entity::~Entity()
{
}

int Entity::getUUID()
{
    return uuid;
}

void Entity::addComponent(shared_ptr<Component> component)
{
    if (componentOperationHandler != nullptr)
    {
        componentOperationHandler->add(shared_from_this(), component);
    }
    else
    {
        addInternal(component);
    }
}

void Entity::removeComponent(shared_ptr<Component> component)
{
    if (componentOperationHandler != nullptr)
    {
        componentOperationHandler->remove(shared_from_this(), component);
    }
    else
    {
        removeInternal(component);
    }
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

void Entity::addInternal(shared_ptr<Component> component)
{
    if (component->index() >= components.size())
    {
        components.resize(static_cast<size_t>(component->index() + 1), nullptr);
    }

    if (components[component->index()] != nullptr)
    {
        removeInternal(component);
    }

    components[component->index()] = component;
    componentBits.set(static_cast<size_t>(component->index()));
}

void Entity::removeInternal(shared_ptr<Component> component)
{
    if (components[component->index()] == nullptr)
    {
        return;
    }

    components[component->index()] = nullptr;
    componentBits.reset(static_cast<size_t>(component->index()));
}
