#pragma once

#include "../src/EntitySystem.h"
#include "../src/EntityEngine.h"
#include "BackgroundCollidableComponent.h"
#include "../src/ComponentFamily.h"

class BackgroundCollisionSystem : public EntitySystem
{
public:
    BackgroundCollisionSystem()
    {
        this->componentFamily = ComponentFamily::one({getComponentTypeId<BackgroundCollidableComponent>()});
    }

    ComponentFamily& getComponentFamily() override
    {
        return *componentFamily;
    }

    void onAddedToEngine(EntityEngine &engine, vector_ptr<entity_ptr> entities) override
    {
        cout << "BackgroundCollisionSystem: I have " << entities->size() << " entities when added" << endl;
    }

    void onRemovedFromEngine(EntityEngine &engine) override
    {
        cout << "BackgroundCollisionSystem: I have been removed" << endl;
    }

    void onEntityAdded(shared_ptr<Entity> entity) override
    {
        cout << "BackgroundCollisionSystem: Entity added" << endl;
    }

    void onEntityRemoved(shared_ptr<Entity> entity) override
    {
        cout << "BackgroundCollisionSystem: Entity removed" << endl;
    }

    void update(vector_ptr<entity_ptr> entities, float deltaTime) override
    {
        cout << "BackgroundCollisionSystem: Colliding..., entities: " << entities->size() << endl;
    }

private:
    shared_ptr<ComponentFamily> componentFamily;
};
