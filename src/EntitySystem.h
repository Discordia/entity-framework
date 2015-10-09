//
// Created by roberts on 2015-10-06.
//

#ifndef ENTITY_FRAMEWORK_ENTITYSYSTEM_H
#define ENTITY_FRAMEWORK_ENTITYSYSTEM_H

#include <memory>

using std::shared_ptr;

class EntityEngine;

class EntitySystem
{
public:
    EntitySystem();
    virtual ~EntitySystem();

    virtual void addedToEngine(shared_ptr<EntityEngine> engine);
    virtual void removedFromEngine(shared_ptr<EntityEngine> engine);
    virtual void update(float deltaTime);
};


#endif //ENTITY_FRAMEWORK_ENTITYSYSTEM_H
