#pragma once

#include "Entity.h"

class EntityOperation
{
public:
    enum EntityOperationType
    {
        ADD,
        REMOVE
    };

    EntityOperation(shared_ptr<Entity> entity, EntityOperationType type)
        : entity(entity), type(type)
    {}

public:
    shared_ptr<Entity> entity;
    EntityOperationType type;
};