#ifndef ENTITY_FRAMEWORK_COMPONENTFAMILY_H
#define ENTITY_FRAMEWORK_COMPONENTFAMILY_H


#include <bitset>
#include <memory>
#include <unordered_map>
#include "Entity.h"

using std::shared_ptr;
using std::bitset;
using std::unordered_map;

struct ComponentFamilyHasher;
class FamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily(bitset<32> allBits, bitset<32> oneBits, bitset<32> excludedBits);
    ~ComponentFamily();

    bool operator==(const ComponentFamily& other) const;
    bool operator!=(const ComponentFamily& other) const;

    int getIndex();
    bool matches(shared_ptr<Entity> entity);

    static FamilyBuilder* all(std::initializer_list<int> componentIndices);
    static FamilyBuilder* one(std::initializer_list<int> componentIndices);
    static FamilyBuilder* exclude(std::initializer_list<int> componentIndices);

private:
    friend struct ComponentFamilyHasher;

    static int family_index;
    static FamilyBuilder* familyBuilder;

    int index;
    bitset<32> allBits;
    bitset<32> oneBits;
    bitset<32> excludedBits;
};

class FamilyBuilder
{
public:
    FamilyBuilder();
    ~FamilyBuilder();

    FamilyBuilder* reset();
    FamilyBuilder* all(std::initializer_list<int> componentIndices);
    FamilyBuilder* one(std::initializer_list<int> componentIndices);
    FamilyBuilder* exclude(std::initializer_list<int> componentIndices);

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

#endif
