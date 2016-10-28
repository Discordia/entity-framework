#pragma once

#include <iostream>
#include "../src/EntitySystem.h"
#include "BackgroundCollidableComponent.h"
#include "RenderableComponent.h"

using std::cout;
using std::endl;

class RenderingSystem : public EntitySystem
{
public:
    RenderingSystem()
    {
        this->componentFamily = ComponentFamily::one({getComponentTypeId<RenderableComponent>()});
    }

    shared_ptr<ComponentFamily> getComponentFamily() override
    {
        return componentFamily;
    }

    void onAddedToEngine(EntityEngine &engine) override
    {
        cout << "RenderingSystem: I have " << engine.getEntitiesFor(*componentFamily)->size() << " entities when added" << endl;
    }

    void update(vector_ptr<entity_ptr> entities, float deltaTime) override
    {
        cout << "Rendering..., entities: " << entities->size() << endl;

        for (auto entity : *entities)
        {
            shared_ptr<RenderableComponent> component = entity->getComponent<RenderableComponent>();
            cout << "Render Component index: " << getComponentTypeId<RenderableComponent>() << ", someMember: " << component-> someMember << endl;
        }
    }

private:
    shared_ptr<ComponentFamily> componentFamily;
};
