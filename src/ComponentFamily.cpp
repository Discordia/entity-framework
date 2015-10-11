#include "ComponentFamily.h"
#include "BitSetUtility.h"

// static init
int ComponentFamily::family_index = 0;
FamilyBuilder* ComponentFamily::familyBuilder = new FamilyBuilder();
unordered_map<std::string, shared_ptr<ComponentFamily>> FamilyBuilder::families;

ComponentFamily::ComponentFamily(bitset<32> allBits, bitset<32> oneBits, bitset<32> excludedBits)
    : index(family_index++), allBits(allBits), oneBits(oneBits), excludedBits(excludedBits)
{
}

ComponentFamily::~ComponentFamily()
{
}

bool ComponentFamily::operator==(const ComponentFamily& other) const
{
    return this->index == other.index;
}

bool ComponentFamily::operator!=(const ComponentFamily& other) const
{
    return this->index != other.index;
}

int ComponentFamily::getIndex()
{
    return index;
}

bool ComponentFamily::matches(shared_ptr<Entity> entity)
{
    bitset<32>& componentBits = entity->getComponentBits();

    if (!BitSetUtility::containsAll(componentBits, allBits))
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

FamilyBuilder* ComponentFamily::all(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->all(componentIndices);
}

FamilyBuilder* ComponentFamily::one(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->one(componentIndices);
}

FamilyBuilder* ComponentFamily::exclude(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->exclude(componentIndices);
}

FamilyBuilder::FamilyBuilder()
{
}

FamilyBuilder::~FamilyBuilder()
{
}

FamilyBuilder* FamilyBuilder::reset()
{
    allBits = bitset<32>();
    oneBits = bitset<32>();
    excludedBits = bitset<32>();

    return this;
}

FamilyBuilder* FamilyBuilder::all(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        allBits.set(static_cast<size_t>(index));
    }

    return this;
}

FamilyBuilder* FamilyBuilder::one(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        oneBits.set(static_cast<size_t>(index));
    }

    return this;
}

FamilyBuilder* FamilyBuilder::exclude(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        excludedBits.set(static_cast<size_t>(index));
    }

    return this;
}

shared_ptr<ComponentFamily> FamilyBuilder::build()
{
    const std::string familyHash = calcFamilyHash(allBits, oneBits, excludedBits);
    auto familyIt = FamilyBuilder::families.find(familyHash);
    if (familyIt != FamilyBuilder::families.end())
    {
        return familyIt->second;
    }

    shared_ptr<ComponentFamily> family = shared_ptr<ComponentFamily>(new ComponentFamily(allBits, oneBits, excludedBits));
    FamilyBuilder::families.insert(std::make_pair(familyHash, family));
    return family;
}

const std::string FamilyBuilder::calcFamilyHash(bitset<32>& allBits, bitset<32>& oneBits, bitset<32>& excludedBits)
{
    std::string familyHash;
    if (allBits.any())
    {
        familyHash.append("all{");
        familyHash.append(allBits.to_string());
        familyHash.append("}");
    }

    if (oneBits.any())
    {
        familyHash.append("one{");
        familyHash.append(oneBits.to_string());
        familyHash.append("}");
    }

    if (excludedBits.any())
    {
        familyHash.append("excluded{");
        familyHash.append(excludedBits.to_string());
        familyHash.append("}");
    }

    return familyHash;
}
