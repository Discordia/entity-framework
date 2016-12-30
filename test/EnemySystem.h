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

    void onAddedToEngine(EntityEngine &engine) override
    {
        cout << "EnemySystem: I have been added to the engine" << endl;
    }

    void onRemovedFromEngine(EntityEngine &engine) override
    {
        cout << "EnemySystem: I have been removed" << endl;
    }

    void onEntityAdded(shared_ptr<Entity> entity) override
    {
        cout << "EnemySystem: Entity added" << endl;
    }

    void onEntityRemoved(shared_ptr<Entity> entity) override
    {
        cout << "EnemySystem: Entity removed" << endl;
    }

    void update(vector_ptr<shared_ptr<Entity>> entities, EntityEngine& engine, float deltaTime) override
    {
        cout << "EnemySystem::update - entities: " << entities->size() << endl;
    }

private:
    ComponentFamily componentFamily;
};