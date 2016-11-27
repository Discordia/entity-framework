#include "ComponentFamilyBuilder.h"
#include "ComponentFamily.h"

unordered_map<string, shared_ptr<ComponentFamily>> ComponentFamilyBuilder::families;

ComponentFamily ComponentFamilyBuilder::create(ComponentBitSet allBits, ComponentBitSet excludedBits)
{
    auto familyHash = calcFamilyHash(allBits, excludedBits);
    auto familyIt = ComponentFamilyBuilder::families.find(familyHash);
    if (familyIt != ComponentFamilyBuilder::families.end())
    {
        return *(familyIt->second);
    }

    auto family = shared_ptr<ComponentFamily>(new ComponentFamily(allBits, excludedBits));
    const pair<string, shared_ptr<ComponentFamily>> familyPair = make_pair(familyHash, family);
    ComponentFamilyBuilder::families.insert(familyPair);

    return *family;
}

const string ComponentFamilyBuilder::calcFamilyHash(ComponentBitSet &allBits, ComponentBitSet &excludedBits)
{
    string familyHash;
    if (allBits.any())
    {
        familyHash.append("all{");
        familyHash.append(allBits.to_string());
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

