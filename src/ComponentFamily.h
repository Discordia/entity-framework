#pragma once

#include "Entity.h"
#include "ComponentFamilyBuilder.h"

class ComponentFamily
{
public:
    ComponentFamily();
    ComponentFamily(ComponentBitSet allBits, ComponentBitSet excludedBits);

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    size_t getIndex() const;
    bool matches(shared_ptr<Entity> entity) const;

    static ComponentFamily none();

    template <class R>
    static ComponentFamily create();

private:
    static bool containsAll(ComponentBitSet& source, const ComponentBitSet& other);
    static bool intersects(ComponentBitSet& source, const ComponentBitSet& other);

private:
    friend struct ComponentFamilyHasher;

    static size_t family_index;
    static ComponentFamilyBuilder familyBuilder;

    size_t index;
    ComponentBitSet allBits;
    ComponentBitSet excludedBits;
};

struct ComponentFamilyHasher
{
    template <class T>
    inline void hash_combine(std::size_t & seed, const T & v) const
    {
        std::hash<T> hasher;
        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    inline std::size_t operator()(const ComponentFamily& componentFamily) const
    {
        size_t seed = 0;
        hash_combine(seed, componentFamily.index);
        return seed;
    }
};


template <class... Args>
struct TypeList {};

struct RequireList{};

template <class... Args>
static ComponentBitSet types(TypeList<Args...> unused) { return ComponentBitSet(); }

template <class T, class... Args>
static ComponentBitSet types(TypeList<T, Args...> unused)
{
    static_assert(std::is_base_of<Component, T>::value, "Invalid component");
    return ComponentBitSet().set(getComponentTypeId<T>()) | types(TypeList<Args...>());
}

template <class... Args>
struct All : TypeList<Args...>, RequireList {};

template <class R>
ComponentFamily ComponentFamily::create()
{
    static_assert(std::is_base_of<RequireList, R>::value, "R is not a RequireList");
    return familyBuilder.create(types(R{}), ComponentBitSet());
}

