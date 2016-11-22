#include "ComponentFamily.h"

// static init
size_t ComponentFamily::family_index = 0;
ComponentFamilyBuilder ComponentFamily::familyBuilder;
unordered_map<string, shared_ptr<ComponentFamily>> ComponentFamilyBuilder::families;

ComponentFamily::ComponentFamily(ComponentBitSet allBits, ComponentBitSet oneBits, ComponentBitSet excludedBits)
    : index(family_index++), allBits(allBits), oneBits(oneBits), excludedBits(excludedBits)
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

size_t ComponentFamily::getIndex() const
{
    return index;
}

bool ComponentFamily::matches(shared_ptr<Entity> entity) const
{
    auto &componentBits = entity->getComponentBits();

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

ComponentFamilyBuilder& ComponentFamily::all(initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().all(componentIndices);
}

ComponentFamilyBuilder& ComponentFamily::one(initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().one(componentIndices);
}

ComponentFamilyBuilder& ComponentFamily::exclude(initializer_list<size_t> componentIndices)
{
    return familyBuilder.reset().exclude(componentIndices);
}

ComponentFamilyBuilder& ComponentFamily::none()
{
    return familyBuilder.reset().excludeAll();
}

bool ComponentFamily::containsAll(ComponentBitSet& source, const ComponentBitSet& other)
{
    auto count = other.count();
    auto result = source & other;

    return result.count() == count;
}

bool ComponentFamily::intersects(ComponentBitSet& source, const ComponentBitSet& other)
{
    ComponentBitSet result = source & other;
    return result.any();
}

ComponentFamilyBuilder& ComponentFamilyBuilder::reset()
{
    allBits = ComponentBitSet();
    oneBits = ComponentBitSet();
    excludedBits = ComponentBitSet();

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::all(initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        allBits.set(index);
    }

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::one(initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        oneBits.set(index);
    }

    return *this;
}

ComponentFamilyBuilder& ComponentFamilyBuilder::exclude(initializer_list<size_t> componentIndices)
{
    for (auto index : componentIndices)
    {
        excludedBits.set(index);
    }

    return *this;
}

ComponentFamilyBuilder &ComponentFamilyBuilder::excludeAll()
{
    excludedBits.flip();
    return *this;
}

ComponentFamilyBuilder::operator shared_ptr<ComponentFamily>()
{
    auto familyHash = calcFamilyHash(allBits, oneBits, excludedBits);
    auto familyIt = ComponentFamilyBuilder::families.find(familyHash);
    if (familyIt != ComponentFamilyBuilder::families.end())
    {
        return familyIt->second;
    }

    auto family = shared_ptr<ComponentFamily>(new ComponentFamily(allBits, oneBits, excludedBits));
    const pair<string, shared_ptr<ComponentFamily>> familyPair = make_pair(familyHash, family);
    ComponentFamilyBuilder::families.insert(familyPair);

    return family;
}

const string ComponentFamilyBuilder::calcFamilyHash(ComponentBitSet &allBits, ComponentBitSet &oneBits, ComponentBitSet &excludedBits)
{
    string familyHash;
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
