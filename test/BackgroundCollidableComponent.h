#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H

#include "../src/Component.h"

class BackgroundCollidableComponent : public Component
{
public:
    BackgroundCollidableComponent() {}
    ~BackgroundCollidableComponent() {}

    int index();

public:
    static int INDEX;
};

#endif
