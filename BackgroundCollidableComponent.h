//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H


#include "Component.h"

class BackgroundCollidableComponent : public Component
{
public:

    BackgroundCollidableComponent();
    virtual ~BackgroundCollidableComponent();

    virtual int index() override;
};


#endif //ENTITY_FRAMEWORK_BACKGROUNDCOLLIDABLECOMPONENT_H
