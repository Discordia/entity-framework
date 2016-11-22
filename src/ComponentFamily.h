#pragma once

#include "Entity.h"

class ComponentFamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily(ComponentBitSet allBits, ComponentBitSet oneBits, ComponentBitSet excludedBits);

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    size_t getIndex() const;
    bool matches(shared_ptr<Entity> entity) const;

    static ComponentFamilyBuilder& all(initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& one(initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& exclude(initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& none();

private:
    static bool containsAll(ComponentBitSet& source, const ComponentBitSet& other);
    static bool intersects(ComponentBitSet& source, const ComponentBitSet& other);

private:
    friend struct ComponentFamilyHasher;

    static size_t family_index;
    static ComponentFamilyBuilder familyBuilder;

    size_t index;
    ComponentBitSet allBits;
    ComponentBitSet oneBits;
    ComponentBitSet excludedBits;
};

class ComponentFamilyBuilder
{
public:
    ComponentFamilyBuilder& reset();
    ComponentFamilyBuilder& all(initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder& one(initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder& exclude(initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder& excludeAll();

    operator shared_ptr<ComponentFamily>();

private:
    static const string calcFamilyHash(ComponentBitSet& allBits, ComponentBitSet& oneBits, ComponentBitSet& excludedBits);

private:
    ComponentBitSet allBits;
    ComponentBitSet oneBits;
    ComponentBitSet excludedBits;

    static unordered_map<string, shared_ptr<ComponentFamily>> families;
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
