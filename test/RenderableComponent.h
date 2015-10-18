#ifndef ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
#define ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H

#include "../src/Component.h"

class RenderableComponent : public Component
{
public:
    RenderableComponent(int i)
        : someMember(i)
    {}

    ~RenderableComponent() {}

    const size_t index();

public:
    const static size_t INDEX;

    int someMember;
};

const size_t RenderableComponent::INDEX = 1;

const size_t RenderableComponent::index()
{
    return INDEX;
}

#endif
