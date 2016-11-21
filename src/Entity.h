#pragma once

#include "Component.h"
#include "ComponentOperationHandler.h"

using entity_ptr =  shared_ptr<Entity>;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    Entity(int32_t uuid, shared_ptr<ComponentOperationHandler> componentOperationHandler);

    int32_t getUUID();

    template<class T, class... Args>
    void addComponent(Args&&... args);

    template<class T>
    void removeComponent();

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

template<class T, class... Args>
void Entity::addComponent(Args&&... args)
{
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Component");

    auto component = shared_ptr<T>(new T{std::forward<Args>(args)...});
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
void Entity::removeComponent()
{
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Component");

    if (componentOperationHandler != nullptr)
    {
        auto component = getComponent<T>();
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
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Component");

    auto componentId = getComponentTypeId<T>();
    if (componentId >= components.size())
    {
        return shared_ptr<T>();
    }

    return std::dynamic_pointer_cast<T>(components[componentId]);
}