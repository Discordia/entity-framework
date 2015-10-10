//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H
#define ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H


#include <iostream>
#include "../src/EntitySystem.h"
#include "../src/EntityEngine.h"
#include "BackgroundCollidableComponent.h"
#include "../src/ComponentFamily.h"

using std::cout;
using std::endl;

class BackgroundCollisionSystem : public EntitySystem
{
public:


    virtual void addedToEngine(shared_ptr<EntityEngine> engine)
    {
        shared_ptr<ComponentFamily> componentFamily = ComponentFamily::one({BackgroundCollidableComponent::INDEX})->build();
        const shared_ptr<vector<shared_ptr<Entity>>> entities = engine->getEntitiesFor(*componentFamily);

        cout << "Number of entites: " << entities->size() << endl;
    }

    void update(float deltaTime) {
        cout << "Colliding..." << endl;
    }
};


#endif //ENTITY_FRAMEWORK_BACKGROUNDCOLLISIONSYSTEM_H
