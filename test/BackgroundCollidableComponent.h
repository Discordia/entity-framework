#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H

#include "../src/Component.h"

class BackgroundCollidableComponent : public Component
{
public:
    BackgroundCollidableComponent() {}
    ~BackgroundCollidableComponent() {}

    const size_t index();

public:
    const static size_t INDEX;
};

#endif
