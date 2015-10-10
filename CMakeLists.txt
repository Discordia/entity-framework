cmake_minimum_required(VERSION 2.8)
project(entity_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        test/main.cpp
        test/BackgroundCollidableComponent.cpp
        test/BackgroundCollidableComponent.h
        test/RenderableComponent.h
        test/RenderingSystem.h
        test/BackgroundCollisionSystem.h
        src/EntityEngine.cpp
        src/EntityEngine.h
        src/EntitySystem.h
        src/EntitySystem.cpp
        src/Component.h
        src/Entity.cpp
        src/Entity.h
        src/EntityOperation.h
        src/ComponentOperationHandler.h
        src/ComponentOperationHandler.cpp
        src/ComponentFamily.cpp
        src/ComponentFamily.h
        src/BitSetUtility.h)
add_executable(entityframework ${SOURCE_FILES})