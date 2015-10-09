//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
#define ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H


#include "../src/Component.h"

class RenderableComponent : public Component
{
public:

    RenderableComponent()
    { }


    virtual ~RenderableComponent()
    { }


    virtual int index() override;
};


#endif //ENTITY_FRAMEWORK_RENDERABLECOMPONENT_H
