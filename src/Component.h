#ifndef ENTITY_FRAMEWORK_COMPONENT_H
#define ENTITY_FRAMEWORK_COMPONENT_H

#include <cstddef>

class Component
{
public:
    Component() {}
    virtual ~Component() {}

    virtual size_t index() = 0;
};

#endif
