#ifndef ENTITY_FRAMEWORK_ENTITY_H
#define ENTITY_FRAMEWORK_ENTITY_H

#include <memory>
#include <vector>
#include <bitset>
#include "Component.h"

using std::shared_ptr;
using std::vector;
using std::bitset;

class ComponentOperationHandler;

template<class T, class B> struct derived_from {
    static void constraints(T* p) { B* pb = p; }
    derived_from() { void(*p)(T*) = constraints; }
};

class Entity : public std::enable_shared_from_this<Entity>
{
public:
    Entity();
    ~Entity();

    int getUUID();

    void addComponent(shared_ptr<Component> component);
    void removeComponent(shared_ptr<Component> component);
    template<class T> shared_ptr<T> getComponent();

    bitset<32>& getComponentBits();
    bitset<32>& getFamilyBits();

private:
    friend class EntityEngine;

    void setUUID(int uuid);
    void addInternal(shared_ptr<Component> component);
    void removeInternal(shared_ptr<Component> component);

private:
    int uuid;
    vector<shared_ptr<Component>> components;
    shared_ptr<ComponentOperationHandler> componentOperationHandler;
    bitset<32> componentBits;
    bitset<32> familyBits;
};

template<class T>
shared_ptr<T> Entity::getComponent()
{
    // check that template parameter is derived from class Component
    derived_from<T,Component>();

    if (T::INDEX >= components.size())
    {
        return std::shared_ptr<T>();
    }

    return std::dynamic_pointer_cast<T>(components[T::INDEX]);
}

#endif
