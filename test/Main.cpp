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

    shared_ptr<Entity> entity1 = engine.createEntity();
    entity1->addComponent(shared_ptr<BackgroundCollidableComponent>(new BackgroundCollidableComponent()));
    entity1->addComponent(shared_ptr<RenderableComponent>(new RenderableComponent(1)));

    shared_ptr<Entity> entity2 = engine.createEntity();
    entity2->addComponent(shared_ptr<RenderableComponent>(new RenderableComponent(2)));

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
    cout << endl;


    // Forth frame
    cout << "FORTH FRAME" << endl;
    entity3->addComponent(shared_ptr<BackgroundCollidableComponent>(new BackgroundCollidableComponent()));
    engine.update(deltaTime);
    cout << endl;

    return 0;
}