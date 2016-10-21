#pragma once

#include "EntityConfiguration.h"

typedef std::size_t TypeId;

template<typename B>
class ClassTypeId
{
public:
    template<typename T>
    static TypeId getTypeId()
    {
        static const TypeId id = nextTypeId++;
        return id;
    }

private:
    static TypeId nextTypeId;
};

template<typename B>
TypeId ClassTypeId<B>::nextTypeId = 0;
