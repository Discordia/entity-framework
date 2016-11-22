#pragma once

#include "../src/EntitySystem.h"
#include "../src/ComponentFamily.h"

class EnemySystem : public EntitySystem
{
public:
    EnemySystem()
        : componentFamily(ComponentFamily::none())
    {
    }

    const ComponentFamily& getComponentFamily() const override
    {
        return componentFamily;
    }

    void update(vector_ptr<shared_ptr<Entity>> entities, EntityEngine& engine, float deltaTime) override
    {
        cout << "EnemySystem::update - entities: " << entities->size() << endl;
    }

private:
    ComponentFamily componentFamily;
};