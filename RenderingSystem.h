//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_RENDERINGSYSTEM_H
#define ENTITY_FRAMEWORK_RENDERINGSYSTEM_H

#include <iostream>
#include "EntitySystem.h"

using std::cout;
using std::endl;

class RenderingSystem : public EntitySystem
{
    void update(float deltaTime) {
        cout << "Rendering..." << endl;
    }
};


#endif //ENTITY_FRAMEWORK_RENDERINGSYSTEM_H
