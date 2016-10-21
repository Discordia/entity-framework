#pragma once

#include <memory>
#include <vector>
#include <bitset>
#include <type_traits>
#include <utility>
#include "Component.h"
#include "ComponentOperationHandler.h"

using std::shared_ptr;
using std::vector;
using std::bitset;

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();

    int getUUID();

    template<class T>
    void addComponent(shared_ptr<T> component);

    template<class T>
    void removeComponent(shared_ptr<T> component);

    template<class T>
    shared_ptr<T> getComponent();

    bitset<32>& getComponentBits();
    bitset<32>& getFamilyBits();

private:
    friend class EntityEngine;

    void setUUID(int uuid);
    void addInternal(shared_ptr<Component> component, TypeId componentId);
    void removeInternal(TypeId componentId);

private:
    int uuid;
    vector<shared_ptr<Component>> components;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
    bitset<32> componentBits;
    bitset<32> familyBits;
};

template<class T>
void Entity::addComponent(shared_ptr<T> component)
{
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Comnponent");

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
    static_assert(std::is_base_of<Component, T>(), "T needs to be derived from Comnponent");

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
        return std::shared_ptr<T>();
    }

    return std::dynamic_pointer_cast<T>(components[componentId]);
}