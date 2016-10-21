#pragma once

#include "ClassTypeId.h"

class Component
{
public:
    virtual ~Component() {}
};


template<class T>
TypeId getComponentTypeId()
{
    return ClassTypeId<Component>::getTypeId<T>();
}

