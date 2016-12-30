#pragma once

#include "../src/EntitySystem.h"
#include "../src/ComponentFamily.h"
#include "PlayerComponent.h"
#include "ControlComponent.h"

class PlayerSystem : public EntitySystem
{
public:
    PlayerSystem()
        : componentFamily(ComponentFamily::create<All<PlayerComponent>>())
    {
    }

    const ComponentFamily& getComponentFamily() const override
    {
        return componentFamily;
    }

    void onAddedToEngine(EntityEngine& engine) override
    {
        cout << "PlayerSystem: I have been added to the engine" << endl;

        ComponentFamily controlFamily = ComponentFamily::create<All<ControlComponent>>();
        controlEntities = engine.getEntities(controlFamily);
    }

    void onRemovedFromEngine(EntityEngine &engine) override
    {
        cout << "PlayerSystem: I have been removed" << endl;
    }

    void onEntityAdded(shared_ptr<Entity> entity) override
    {
        cout << "PlayerSystem: Entity added" << endl;
    }

    void onEntityRemoved(shared_ptr<Entity> entity) override
    {
        cout << "PlayerSystem: Entity removed" << endl;
    }

    void update(vector_ptr<shared_ptr<Entity>> entities, EntityEngine& engine, float deltaTime) override
    {
        cout << "Player entities: " << entities->size() << endl;
        cout << "Control entities: " << controlEntities->size() << endl;
    }

private:
    ComponentFamily componentFamily;
    vector_ptr<entity_ptr> controlEntities;
};