#pragma once

#include <bitset>
#include <memory>
#include <unordered_map>
#include "Entity.h"

using std::shared_ptr;
using std::bitset;
using std::unordered_map;

struct ComponentFamilyHasher;
class ComponentFamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily(bitset<32> allBits, bitset<32> oneBits, bitset<32> excludedBits);
    ~ComponentFamily();

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    size_t getIndex();
    bool matches(shared_ptr<Entity> entity);

    static ComponentFamilyBuilder* all(std::initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder* one(std::initializer_list<size_t> componentIndices);
    static ComponentFamilyBuilder* exclude(std::initializer_list<size_t> componentIndices);

private:
    static bool containsAll(bitset<32>& source, bitset<32>& other);
    static bool intersects(bitset<32>& source, bitset<32>& other);

private:
    friend struct ComponentFamilyHasher;

    static int family_index;
    static ComponentFamilyBuilder* familyBuilder;

    size_t index;
    bitset<32> allBits;
    bitset<32> oneBits;
    bitset<32> excludedBits;
};

class ComponentFamilyBuilder
{
public:
    ComponentFamilyBuilder();
    ~ComponentFamilyBuilder();

    ComponentFamilyBuilder* reset();
    ComponentFamilyBuilder* all(std::initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder* one(std::initializer_list<size_t> componentIndices);
    ComponentFamilyBuilder* exclude(std::initializer_list<size_t> componentIndices);

    shared_ptr<ComponentFamily> build();

private:
    static const std::string calcFamilyHash(bitset<32>& allBits, bitset<32>& oneBits, bitset<32>& excludedBits);

private:
    bitset<32> allBits;
    bitset<32> oneBits;
    bitset<32> excludedBits;

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
