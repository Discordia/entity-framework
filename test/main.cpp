#include <memory>

#include "../src/EntityEngine.h"

#include "RenderingSystem.h"
#include "BackgroundCollisionSystem.h"

using namespace std;

int main()
{
    shared_ptr<EntityEngine> engine = shared_ptr<EntityEngine>(new EntityEngine);
    engine->addSystem(shared_ptr<EntitySystem>(new BackgroundCollisionSystem()));
    engine->addSystem(shared_ptr<EntitySystem>(new RenderingSystem()));

    shared_ptr<Entity> entity1 = shared_ptr<Entity>(new Entity());
    entity1->addComponent(shared_ptr<Component>(new BackgroundCollidableComponent()));
    entity1->addComponent(shared_ptr<Component>(new RenderableComponent()));
    engine->addEntity(entity1);

    shared_ptr<Entity> entity2 = shared_ptr<Entity>(new Entity());
    entity2->addComponent(shared_ptr<Component>(new RenderableComponent()));
    engine->addEntity(entity2);

    for (int i = 0; i < 10; i++) {
        float deltaTime = 0.016f;

        engine->update(deltaTime);
    }

    return 0;
}