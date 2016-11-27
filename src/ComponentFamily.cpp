#include "ComponentFamily.h"

size_t ComponentFamily::family_index = 0;
ComponentFamilyBuilder ComponentFamily::familyBuilder;

ComponentFamily::ComponentFamily()
    : index(family_index++)
{
    excludedBits.flip();
}

ComponentFamily::ComponentFamily(ComponentBitSet allBits, ComponentBitSet excludedBits)
    : index(family_index++), allBits(allBits), excludedBits(excludedBits)
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

    return !(excludedBits.any() && ComponentFamily::intersects(componentBits, excludedBits));
}

ComponentFamily ComponentFamily::none()
{
    return ComponentFamily();
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