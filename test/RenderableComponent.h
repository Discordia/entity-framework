#pragma once

#include "../src/Component.h"

class RenderableComponent : public Component
{
public:
    RenderableComponent(int i)
        : someMember(i)
    {}

public:
    int someMember;
};
