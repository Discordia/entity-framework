//
// Created by roberts on 2015-10-09.
//

#ifndef ENTITY_FRAMEWORK_COMPONENTFAMILY_H
#define ENTITY_FRAMEWORK_COMPONENTFAMILY_H


#include <bitset>
#include <memory>
#include "Entity.h"

using std::shared_ptr;
using std::bitset;

class FamilyBuilder;

class ComponentFamily
{
public:
    ComponentFamily();
    ~ComponentFamily();

    int getIndex();
    bool matches(shared_ptr<Entity> entity);

    static shared_ptr<FamilyBuilder> all(std::initializer_list<int> componentIndices);
    static shared_ptr<FamilyBuilder> one(std::initializer_list<int> componentIndices);
    static shared_ptr<FamilyBuilder> exclude(std::initializer_list<int> componentIndices);

private:
    static int family_index;
    static shared_ptr<FamilyBuilder> familyBuilder;

    int index;
    bitset<32> allBits;
    bitset<32> oneBits;
    bitset<32> excludedBits;
};

class FamilyBuilder : std::enable_shared_from_this<FamilyBuilder>
{
public:
    FamilyBuilder();
    ~FamilyBuilder();

    shared_ptr<FamilyBuilder> reset();
    shared_ptr<FamilyBuilder> all(std::initializer_list<int> componentIndices);
    shared_ptr<FamilyBuilder> one(std::initializer_list<int> componentIndices);
    shared_ptr<FamilyBuilder> exclude(std::initializer_list<int> componentIndices);

private:
    bitset<32> allBits;
    bitset<32> oneBits;
    bitset<32> excludedBits;
};


#endif //ENTITY_FRAMEWORK_COMPONENTFAMILY_H
