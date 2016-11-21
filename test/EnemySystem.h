#pragma once

#include "../src/EntitySystem.h"
#include "../src/ComponentFamily.h"

class EnemySystem : public EntitySystem
{
public:
    EnemySystem()
    {
        componentFamily = ComponentFamily::none();
    }

    ComponentFamily& getComponentFamily()
    {
        return *componentFamily;
    }

    void update(vector_ptr<shared_ptr<Entity>> entities, EntityEngine* engine, float deltaTime)
    {
        cout << "EnemySystem::update - entities: " << entities->size() << endl;
    }

private:
    shared_ptr<ComponentFamily> componentFamily;
};