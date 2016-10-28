#include "ComponentFamily.h"

// static init
size_t ComponentFamily::family_index = 0;
ComponentFamilyBuilder ComponentFamily::familyBuilder;
unordered_map<std::string, shared_ptr<ComponentFamily>> ComponentFamilyBuilder::families;

ComponentFamily::ComponentFamily(ComponentBitSet allBits, ComponentBitSet oneBits, ComponentBitSet excludedBits)
    : index(family_index++), allBits(allBits), oneBits(oneBits), excludedBits(excludedBits)
{
}

ComponentFamily::~ComponentFamily()
{
}

bool ComponentFamily::operator==(const ComponentFamily &other) const
{
    return this->index == other.index;
}

bool ComponentFamily::operator!=(const ComponentFamily &other) const
{
    return this->index != other.index;
}

size_t ComponentFamily::getIndex()
{
    return index;
}

bool ComponentFamily::matches(shared_ptr<Entity> entity)
{
    ComponentBitSet &componentBits = entity->getComponentBits();

    if (!ComponentFamily::containsAll(componentBits, allBits))
    {
        return false;
    }

    if (oneBits.any() && !ComponentFamily::intersects(componentBits, oneBits))
    {
        return false;
    }

    return !(excludedBits.any() && ComponentFamily::intersects(componentBits, excludedBits));
}

ComponentFamilyBuilder& ComponentFamily::all(std::initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().all(componentIndices);
}

ComponentFamilyBuilder& ComponentFamily::one(std::initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().one(componentIndices);
}

ComponentFamilyBuilder& ComponentFamily::exclude(std::initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().exclude(componentIndices);
}

bool ComponentFamily::containsAll(ComponentBitSet &source, ComponentBitSet &other)
{
    size_t count = other.count();
    ComponentBitSet result = source & other;

    return result.count() == count;
}

bool ComponentFamily::intersects(ComponentBitSet &source, ComponentBitSet &other)
{
    ComponentBitSet result = source & other;
    return result.any();
}

ComponentFamilyBuilder::ComponentFamilyBuilder()
{
}

ComponentFamilyBuilder::~ComponentFamilyBuilder()
{
}

ComponentFamilyBuilder& ComponentFamilyBuilder::reset()
{
    allBits = ComponentBitSet();
    oneBits = ComponentBitSet();
    excludedBits = ComponentBitSet();

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::all(std::initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        allBits.set(index);
    }

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::one(std::initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        oneBits.set(index);
    }

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::exclude(std::initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        excludedBits.set(index);
    }

    return *this;
}

shared_ptr<ComponentFamily> ComponentFamilyBuilder::build()
{
    const std::string familyHash = calcFamilyHash(allBits, oneBits, excludedBits);
    auto familyIt = ComponentFamilyBuilder::families.find(familyHash);
    if (familyIt != ComponentFamilyBuilder::families.end())
    {
        return familyIt->second;
    }

    shared_ptr<ComponentFamily> family = shared_ptr<ComponentFamily>(
            new ComponentFamily(allBits, oneBits, excludedBits));
    ComponentFamilyBuilder::families.insert(std::make_pair(familyHash, family));
    return family;
}

const std::string ComponentFamilyBuilder::calcFamilyHash(ComponentBitSet &allBits, ComponentBitSet &oneBits, ComponentBitSet &excludedBits)
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
