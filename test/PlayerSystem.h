#pragma once

#include "../src/EntitySystem.h"
#include "../src/ComponentFamily.h"
#include "PlayerComponent.h"
#include "ControlComponent.h"

class PlayerSystem : public EntitySystem
{
public:
    PlayerSystem()
        : componentFamily(ComponentFamily::one({getComponentTypeId<PlayerComponent>()}))
    {
    }

    const ComponentFamily& getComponentFamily() const override
    {
        return componentFamily;
    }

    void onAddedToEngine(EntityEngine& engine) override
    {
        ComponentFamily controlFamily = ComponentFamily::one({getComponentTypeId<ControlComponent>()});
        controlEntities = engine.getEntities(controlFamily);
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