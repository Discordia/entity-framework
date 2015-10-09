cmake_minimum_required(VERSION 2.8)
project(entity_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        EntityEngine.cpp
        EntityEngine.h
        EntitySystem.h
        RenderingSystem.cpp
        RenderingSystem.h
        EntitySystem.cpp
        BackgroundCollisionSystem.cpp
        BackgroundCollisionSystem.h
        Component.h
        BackgroundCollidableComponent.cpp
        BackgroundCollidableComponent.h
        RenderableComponent.cpp
        RenderableComponent.h
        Entity.cpp
        Entity.h
        EntityOperation.h
        ComponentOperationHandler.h
        ComponentOperationHandler.cpp)
add_executable(entityframework ${SOURCE_FILES})