#pragma once

#include "EntityConfiguration.h"

class ComponentFamily;

class ComponentFamilyBuilder
{
public:
    ComponentFamily create(ComponentBitSet allBits, ComponentBitSet excludedBits);

private:
    static const string calcFamilyHash(ComponentBitSet& allBits, ComponentBitSet& excludedBits);

private:
    static unordered_map<string, shared_ptr<ComponentFamily>> families;
};