#pragma once

#include "Component.h"
#include "ComponentOperationHandler.h"

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    Entity(int32_t uuid, shared_ptr<ComponentOperationHandler> componentOperationHandler);

    int32_t getUUID();

    template<class T>
    void addComponent(shared_ptr<T> component);

    template<class T>
    void removeComponent(shared_ptr<T> component);

    template<class T>
    shared_ptr<T> getComponent();

    ComponentBitSet& getComponentBits();
    ComponentBitSet& getFamilyBits();

private:
    friend class EntityEngine;

    void setUUID(int32_t uuid);
    void resetUUID();

    void addInternal(shared_ptr<Component> component, TypeId componentId);
    void removeInternal(TypeId componentId);

private:
    int32_t uuid;
    array<shared_ptr<Component>, MAX_COMPONENTS> components;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
    ComponentBitSet componentBits;
    ComponentBitSet familyBits;
};

template<class T>
void Entity::addComponent(shared_ptr<T> component)
{
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Component");

    if (componentOperationHandler != nullptr)
    {
        componentOperationHandler->add(shared_from_this(), component, getComponentTypeId<T>());
    }
    else
    {
        addInternal(component, getComponentTypeId<T>());
    }
}

template<class T>
void Entity::removeComponent(shared_ptr<T> component)
{
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Component");

    if (componentOperationHandler != nullptr)
    {
        componentOperationHandler->remove(shared_from_this(), component, getComponentTypeId<T>());
    }
    else
    {
        removeInternal(getComponentTypeId<T>());
    }
}

template<class T>
shared_ptr<T> Entity::getComponent()
{
    // check that template parameter is derived from class Component
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Comnponent");

    TypeId componentId = getComponentTypeId<T>();
    if (componentId >= components.size())
    {
        return shared_ptr<T>();
    }

    return std::dynamic_pointer_cast<T>(components[componentId]);
}