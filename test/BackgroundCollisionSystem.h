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
        this->entities = engine->getEntitiesFor(*componentFamily);
    }

    void update(float deltaTime) {
        cout << "Colliding..., entities: " << entities->size() << endl;
    }

private:
    shared_ptr<vector<shared_ptr<Entity>>> entities;
};

#endif
