#include "ComponentFamily.h"
#include "BitSetUtility.h"

// static init
int ComponentFamily::family_index = 0;
ComponentFamilyBuilder* ComponentFamily::familyBuilder = new ComponentFamilyBuilder();
unordered_map<std::string, shared_ptr<ComponentFamily>> ComponentFamilyBuilder::families;

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

ComponentFamilyBuilder* ComponentFamily::all(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->all(componentIndices);
}

ComponentFamilyBuilder* ComponentFamily::one(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->one(componentIndices);
}

ComponentFamilyBuilder* ComponentFamily::exclude(std::initializer_list<int> componentIndices)
{
    return familyBuilder->reset()->exclude(componentIndices);
}

ComponentFamilyBuilder::ComponentFamilyBuilder()
{
}

ComponentFamilyBuilder::~ComponentFamilyBuilder()
{
}

ComponentFamilyBuilder* ComponentFamilyBuilder::reset()
{
    allBits = bitset<32>();
    oneBits = bitset<32>();
    excludedBits = bitset<32>();

    return this;
}

ComponentFamilyBuilder* ComponentFamilyBuilder::all(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        allBits.set(static_cast<size_t>(index));
    }

    return this;
}

ComponentFamilyBuilder* ComponentFamilyBuilder::one(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        oneBits.set(static_cast<size_t>(index));
    }

    return this;
}

ComponentFamilyBuilder* ComponentFamilyBuilder::exclude(std::initializer_list<int> componentIndices)
{
    for (auto index : componentIndices)
    {
        excludedBits.set(static_cast<size_t>(index));
    }

    return this;
}

shared_ptr<ComponentFamily> ComponentFamilyBuilder::build()
{
    const std::string familyHash = calcFamilyHash(allBits, oneBits, excludedBits);
    auto familyIt = ComponentFamilyBuilder::families.find(familyHash);
    if (familyIt != ComponentFamilyBuilder::families.end())
    {
        return familyIt->second;
    }

    shared_ptr<ComponentFamily> family = shared_ptr<ComponentFamily>(new ComponentFamily(allBits, oneBits, excludedBits));
    ComponentFamilyBuilder::families.insert(std::make_pair(familyHash, family));
    return family;
}

const std::string ComponentFamilyBuilder::calcFamilyHash(bitset<32>& allBits, bitset<32>& oneBits, bitset<32>& excludedBits)
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
