//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H


#include <iostream>
#include "EntitySystem.h"

using std::cout;
using std::endl;

class BackgroundCollisionSystem : public EntitySystem
{
public:
    void update(float deltaTime) {
        cout << "Colliding..." << endl;
    }
};


#endif //ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H
