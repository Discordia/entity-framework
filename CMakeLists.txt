cmake_minimum_required(VERSION 2.8)
project(entity_framework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${root_SOURCE_DIR}/src)

set(SOURCE_FILES
        test/main.cpp
        src/EntityEngine.cpp
        src/EntityEngine.h
        src/EntitySystem.h
        test/RenderingSystem.cpp
        test/RenderingSystem.h
        src/EntitySystem.cpp
        test/BackgroundCollisionSystem.cpp
        test/BackgroundCollisionSystem.h
        src/Component.h
        test/BackgroundCollidableComponent.cpp
        test/BackgroundCollidableComponent.h
        test/RenderableComponent.cpp
        test/RenderableComponent.h
        src/Entity.cpp
        src/Entity.h
        src/EntityOperation.h
        src/ComponentOperationHandler.h
        src/ComponentOperationHandler.cpp)
add_executable(entityframework ${SOURCE_FILES})