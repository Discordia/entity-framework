#ifndef ENTITY_FRAMEWORK_COMPONENT_H
#define ENTITY_FRAMEWORK_COMPONENT_H


class Component
{
public:
    Component() {}
    virtual ~Component() {}

    virtual int index() = 0;
};

#endif
