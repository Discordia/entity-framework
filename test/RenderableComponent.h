#ifndef ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
#define ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H

#include "../src/Component.h"

class RenderableComponent : public Component
{
public:
    RenderableComponent() {}
    ~RenderableComponent() {}

    size_t index();

public:
    static size_t INDEX;
};

size_t RenderableComponent::INDEX = 1;

size_t RenderableComponent::index()
{
    return INDEX;
}

#endif
