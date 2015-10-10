//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H

#include "../src/Component.h"

class BackgroundCollidableComponent : public Component
{
public:

    BackgroundCollidableComponent();
    virtual ~BackgroundCollidableComponent();

    virtual int index();

public:
    static int INDEX;
};


#endif //ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
