//
// Created by roberts on 2015-10-09.
//

#include "ComponentFamily.h"
#include "BitSetUtility.h"

int ComponentFamily::family_index = 0;

shared_ptr<FamilyBuilder> ComponentFamily::familyBuilder;

const bitset<32> ZERO_BITS;

ComponentFamily::ComponentFamily()
    : index(family_index++)
{
}

ComponentFamily::~ComponentFamily()
{
}

int ComponentFamily::getIndex()
{
    return index;
}

bool ComponentFamily::matches(shared_ptr<Entity> entity)
{
    bitset<32>& componentBits = entity->getComponentBits();

    if (BitSetUtility::containsAll(componentBits, allBits))
    {
        return false;
    }

    if (oneBits.any() && !BitSetUtility::intersects(componentBits, oneBits))
    {
        return false;
    }

    if (excludedBits.any() && BitSetUtility::intersects(componentBits, excludedBits))
    {
        return false;
    }

    return true;
}

shared_ptr<FamilyBuilder> ComponentFamily::all(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->all(componentIndices);
}

shared_ptr<FamilyBuilder> ComponentFamily::one(std::initializer_list<int> componentIndices)
{
    return familyBuilder;
}

shared_ptr<FamilyBuilder> ComponentFamily::exclude(std::initializer_list<int> componentIndices)
{
    return familyBuilder;
}

FamilyBuilder::FamilyBuilder()
{
}

FamilyBuilder::~FamilyBuilder()
{
}

shared_ptr<FamilyBuilder> FamilyBuilder::reset()
{
    allBits = ZERO_BITS;
    oneBits = ZERO_BITS;
    excludedBits = ZERO_BITS;

    return shared_from_this();
}

shared_ptr<FamilyBuilder> FamilyBuilder::all(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        allBits.set(static_cast<size_t>(index));
    }

    return shared_from_this();
}

shared_ptr<FamilyBuilder> FamilyBuilder::one(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        oneBits.set(static_cast<size_t>(index));
    }

    return shared_from_this();
}

shared_ptr<FamilyBuilder> FamilyBuilder::exclude(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        excludedBits.set(static_cast<size_t>(index));
    }

    return shared_from_this();
}
