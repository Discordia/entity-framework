#include "../src/EntityEngine.h"

#include "RenderingSystem.h"
#include "BackgroundCollisionSystem.h"

int main()
{
    const float deltaTime = 0.016f;

    // First frame
    cout << "FIRST FRAME" << endl;

    EntityEngine engine;
    const shared_ptr<EntitySystem> collisionSystem = shared_ptr<EntitySystem>(new BackgroundCollisionSystem());
    engine.addSystem(collisionSystem);

    shared_ptr<Entity> entity1 = engine.createEntity();
    entity1->addComponent<BackgroundCollidableComponent>();
    entity1->addComponent<RenderableComponent>(1);

    shared_ptr<Entity> entity2 = engine.createEntity();
    entity2->addComponent<RenderableComponent>(2);
    engine.update(deltaTime);


    // Second frame
    cout << endl << "SECOND FRAME" << endl;
    engine.addSystem(shared_ptr<EntitySystem>(new RenderingSystem()));
    engine.update(deltaTime);


    // Third frame
    cout << endl << "THIRD FRAME" << endl;
    shared_ptr<Entity> entity3(new Entity());
    entity3->addComponent<RenderableComponent>(3);
    engine.addEntity(entity3);
    engine.update(deltaTime);


    // Forth frame
    cout << endl << "FORTH FRAME" << endl;
    entity3->addComponent<BackgroundCollidableComponent>();
    engine.update(deltaTime);


    // Fifth frame
    cout << endl << "FIFTH FRAME" << endl;
    entity3->removeComponent<BackgroundCollidableComponent>();
    engine.update(deltaTime);


    // Sixth frame
    cout << endl << "SIXTH FRAME" << endl;
    engine.removeEntity(entity3);
    engine.update(deltaTime);
    
    // Seventh frame
    cout << endl << "SEVENTH FRAME" << endl;
    engine.removeSystem(collisionSystem);
    engine.update(deltaTime);

    return 0;
}