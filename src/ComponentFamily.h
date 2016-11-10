#pragma once

#include "Entity.h"

class ComponentFamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily(ComponentBitSet allBits, ComponentBitSet oneBits, ComponentBitSet excludedBits);

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    size_t getIndex();
    bool matches(shared_ptr<Entity> entity);

    static ComponentFamilyBuilder& all(initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& one(initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder& exclude(initializer_list<size_t> componentIndices);

private:
    static bool containsAll(ComponentBitSet& source, ComponentBitSet& other);
    static bool intersects(ComponentBitSet& source, ComponentBitSet& other);

private:
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

    operator shared_ptr<ComponentFamily>();

private:
    static const string calcFamilyHash(ComponentBitSet& allBits, ComponentBitSet& oneBits, ComponentBitSet& excludedBits);

private:
    ComponentBitSet allBits;
    ComponentBitSet oneBits;
    ComponentBitSet excludedBits;

    static unordered_map<string, shared_ptr<ComponentFamily>> families;
};
