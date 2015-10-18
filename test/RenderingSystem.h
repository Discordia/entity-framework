#ifndef ENTITY_FRAMEWORK_RENDERINGSYSTEM_H
#define ENTITY_FRAMEWORK_RENDERINGSYSTEM_H

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
        shared_ptr<ComponentFamily> componentFamily = ComponentFamily::one({RenderableComponent::INDEX})->build();
        this->entities = engine->getEntitiesFor(*componentFamily);
    }
    
    void update(float deltaTime) {
        cout << "Rendering..., entities: " << entities->size() << endl;

        for (auto entity : *entities)
        {
            shared_ptr<RenderableComponent> component = entity->getComponent<RenderableComponent>();
            cout << "Render Component index: " << component->index() << ", someMember: " << component-> someMember << endl;
        }
    }

private:
    shared_ptr<vector<shared_ptr<Entity>>> entities;
};

#endif

