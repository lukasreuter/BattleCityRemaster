#pragma once

#include "RenderManager.h"
#include <Magnum/Magnum.h>
#include <Magnum/Math/Math.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/SceneGraph/Object.h>
#include <entt.hpp>
#include <map>

using SceneRoot = Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D>;
using SceneNode = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;


struct Collidable {};

struct OverHeating
{
    float overheating, shootHeating, maxheating;
};

struct AI {};

struct Name
{
    std::string name;
};

struct Position
{
    Magnum::Vector3 position;
};

struct Velocity
{
    Magnum::Vector3 velocity, direction;
};

struct Renderable
{
    Renderable() : sceneNode{nullptr} {}
    explicit Renderable(SceneNode* node) : sceneNode{node} {}
    explicit Renderable(std::string nodeName)
    {
        //! @todo fix this return type
        //sceneNode = RenderManager::GetRef().getSceneManager()->getSceneNode(nodeName);
    }

    SceneNode* sceneNode;
};

struct Orientation
{
    Magnum::Quaternion orientation;
};

struct AngularVelocity
{
    Magnum::Vector3 angularVelocity, direction;
};

// this is a single instance component that uniquely identifies the player
struct Player {};

struct AIDriven {};

struct Destroyable
{
    int health, maxHealth;
};

struct Score
{
    int score = 0;
};

struct Children
{
    std::map<std::string, entt::DefaultRegistry::entity_type> children;
};

struct LightComponent
{
    LightComponent() : light{nullptr} {}
    explicit LightComponent(SceneNode* l) : light(l) {}
    
    SceneNode* light = nullptr;
};
