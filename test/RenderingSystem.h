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
    void addedToEngine(shared_ptr<EntityEngine> engine)
    {
        shared_ptr<ComponentFamily> componentFamily = ComponentFamily::one({getComponentTypeId<RenderableComponent>()})->build();
        this->entities = engine->getEntitiesFor(*componentFamily);
    }
    
    void update(float deltaTime) {
        cout << "Rendering..., entities: " << entities->size() << endl;

        for (auto entity : *entities)
        {
            shared_ptr<RenderableComponent> component = entity->getComponent<RenderableComponent>();
            cout << "Render Component index: " << getComponentTypeId<RenderableComponent>() << ", someMember: " << component-> someMember << endl;
        }
    }

private:
    shared_ptr<vector<shared_ptr<Entity>>> entities;
};
