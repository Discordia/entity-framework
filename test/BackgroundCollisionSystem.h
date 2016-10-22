#pragma once

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
    BackgroundCollisionSystem()
    {
        this->componentFamily = ComponentFamily::one({getComponentTypeId<BackgroundCollidableComponent>()})->build();
    }

    shared_ptr<ComponentFamily> getComponentFamily() override
    {
        return componentFamily;
    }

    void onAddedToEngine(EntityEngine &engine) override
    {
        cout << "BackgroundCollisionSystem: I have " << engine.getEntitiesFor(*componentFamily)->size() << " entities when added" << endl;
    }

    void update(vector_ptr<entity_ptr> entities, float deltaTime) override
    {
        cout << "BackgroundCollisionSystem: Colliding..., entities: " << entities->size() << endl;
    }

private:
    shared_ptr<ComponentFamily> componentFamily;
};
