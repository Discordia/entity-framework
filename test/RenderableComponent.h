//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
#define ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H


#include "../src/Component.h"

class RenderableComponent : public Component
{
public:
    RenderableComponent() {}
    ~RenderableComponent() {}

    int index();

public:
    static int INDEX;
};

int RenderableComponent::INDEX = 1;

int RenderableComponent::index()
{
    return INDEX;
}

#endif //ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
