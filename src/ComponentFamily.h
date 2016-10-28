#pragma once

#include "Entity.h"

struct ComponentFamilyHasher;
class ComponentFamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily(ComponentBitSet allBits, ComponentBitSet oneBits, ComponentBitSet excludedBits);
    ~ComponentFamily();

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    size_t getIndex();
    bool matches(shared_ptr<Entity> entity);

    static ComponentFamilyBuilder& all(std::initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& one(std::initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& exclude(std::initializer_list<size_t> componentIndices);

private:
    static bool containsAll(ComponentBitSet& source, ComponentBitSet& other);
    static bool intersects(ComponentBitSet& source, ComponentBitSet& other);

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
    ComponentFamilyBuilder();
    ~ComponentFamilyBuilder();

    ComponentFamilyBuilder& reset();
    ComponentFamilyBuilder& all(std::initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder& one(std::initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder& exclude(std::initializer_list<size_t> componentIndices);

    shared_ptr<ComponentFamily> build();

private:
    static const std::string calcFamilyHash(ComponentBitSet& allBits, ComponentBitSet& oneBits, ComponentBitSet& excludedBits);

private:
    ComponentBitSet allBits;
    ComponentBitSet oneBits;
    ComponentBitSet excludedBits;

    static unordered_map<std::string, shared_ptr<ComponentFamily>> families;
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
