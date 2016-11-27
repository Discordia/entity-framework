#pragma once

#include "../src/EntitySystem.h"
#include "BackgroundCollidableComponent.h"
#include "RenderableComponent.h"

class RenderingSystem : public EntitySystem
{
public:
    RenderingSystem()
        : componentFamily(ComponentFamily::create<All<RenderableComponent>>())
    {
    }

    const ComponentFamily& getComponentFamily() const override
    {
        return componentFamily;
    }

    void onAddedToEngine(EntityEngine &engine) override
    {
        cout << "RenderingSystem: I have been added to the engine" << endl;
    }

    void onRemovedFromEngine(EntityEngine &engine) override
    {
        cout << "RenderingSystem: I have been removed" << endl;
    }

    void onEntityAdded(shared_ptr<Entity> entity) override
    {
        cout << "RenderingSystem: Entity added" << endl;
    }

    void onEntityRemoved(shared_ptr<Entity> entity) override
    {
        cout << "RenderingSystem: Entity removed" << endl;
    }

    void update(vector_ptr<entity_ptr> entities, EntityEngine& engine, float deltaTime) override
    {
        cout << "Rendering..., entities: " << entities->size() << endl;

        for (auto entity : *entities)
        {
            shared_ptr<RenderableComponent> component = entity->getComponent<RenderableComponent>();
            cout << "Render Component index: " << getComponentTypeId<RenderableComponent>() << ", someMember: " << component-> someMember << endl;
        }
    }

private:
    ComponentFamily componentFamily;
};
