//
// Created by roberts on 2015-10-06.
//

#include "Entity.h"
#include "ComponentOperationHandler.h"

Entity::Entity()
    : uuid(0)
{
}

Entity::~Entity()
{
}

void Entity::addComponent(shared_ptr<Component> component)
{
    if (componentOperationHandler != nullptr)
    {
        componentOperationHandler->add(this, component);
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
        componentOperationHandler->remove(this, component);
    }
    else
    {
        removeInternal(component);
    }
}

int Entity::getUUID()
{
    return uuid;
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
}

void Entity::removeInternal(shared_ptr<Component> component)
{
    if (components[component->index()] == nullptr)
    {
        return;
    }

    components[component->index()] = nullptr;
}