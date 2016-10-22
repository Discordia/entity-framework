#include <memory>

#include "../src/EntityEngine.h"

#include "RenderingSystem.h"
#include "BackgroundCollisionSystem.h"

using namespace std;

int main()
{
    const float deltaTime = 0.016f;

    // First frame
    cout << "FIRST FRAME" << endl;

    EntityEngine engine;
    engine.addSystem(shared_ptr<EntitySystem>(new BackgroundCollisionSystem()));

    shared_ptr<Entity> entity1 = shared_ptr<Entity>(new Entity());
    entity1->addComponent(shared_ptr<BackgroundCollidableComponent>(new BackgroundCollidableComponent()));
    entity1->addComponent(shared_ptr<RenderableComponent>(new RenderableComponent(1)));
    engine.addEntity(entity1);

    shared_ptr<Entity> entity2 = shared_ptr<Entity>(new Entity());
    entity2->addComponent(shared_ptr<RenderableComponent>(new RenderableComponent(2)));
    engine.addEntity(entity2);

    engine.update(deltaTime);
    cout << endl;


    // Second frame
    cout << "SECOND FRAME" << endl;
    engine.addSystem(shared_ptr<EntitySystem>(new RenderingSystem()));
    engine.update(deltaTime);
    cout << endl;


    // Third frame
    cout << "THIRD FRAME" << endl;
    shared_ptr<Entity> entity3(new Entity());
    entity3->addComponent(shared_ptr<RenderableComponent>(new RenderableComponent(3)));
    engine.addEntity(entity3);
    engine.update(deltaTime);

    return 0;
}