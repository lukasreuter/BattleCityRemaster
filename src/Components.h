#pragma once

#include <Magnum/Magnum.h>
#include <Magnum/Math/Math.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/SceneGraph/Object.h>

//#include <OGRE/OgreSceneManager.h>
//#include <OGRE/OgreSceneNode.h>
//#include <OGRE/OgreMovableObject.h>
//#include <OGRE/OgreQuaternion.h>
#include "RenderManager.h"
//#include <OIS/OIS.h>
//#include <OGRE/SdkTrays.h>



#include <map>
#include <entt.hpp>


typedef Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D> SceneRoot;
typedef Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D> SceneNode;



struct Collidable {};

struct OverHeating
{
    //OverHeating(float overheating, float shootHeating, float maxheating) : overheating(overheating), shootHeating(shootHeating), maxheating(maxheating) {}
    
    float overheating;
    float shootHeating;
    float maxheating;
};

struct AI {};

struct Name
{
    //Name(std::string name) : name{name} {}
    
    std::string name;
};

struct Position
{
//    Position() : Position(0.f, 0.f, 0.f) {}
//    Position(Magnum::Vector3 position) : position{position} {}
//    Position(float x, float y, float z) : position{x, y, z} {}

    Magnum::Vector3 position;
};

struct Velocity
{
//    Velocity() : Velocity(0.f, 0.f, 0.f) {}
//    Velocity(Magnum::Vector3 velocity) : velocity{velocity}, direction{0.f, 0.f, 0.f} {}
//    Velocity(float x, float y, float z) : velocity{x, y, z}, direction{0.f, 0.f, 0.f} {}

    Magnum::Vector3 velocity;
    Magnum::Vector3 direction;
};

struct Renderable
{
    Renderable() : sceneNode{nullptr} {}
    Renderable(SceneNode* node) : sceneNode{node} {}
    Renderable(std::string nodeName)
    {
        //! @todo fix this return type
        //sceneNode = RenderManager::GetRef().getSceneManager()->getSceneNode(nodeName);
    }

    SceneNode* sceneNode;
};

using namespace Magnum::Math::Literals;

struct Orientation
{
//    Orientation() : orientation{} {}
//    Orientation(Magnum::Deg angle, const Magnum::Vector3 axis) : orientation{axis, float(angle)} {}
//    Orientation(Magnum::Quaternion quaternion) : orientation{quaternion} {}

    Magnum::Quaternion orientation;
};

struct AngularVelocity
{
//    AngularVelocity() : AngularVelocity{0.f, 0.f, 0.f} {}
//    AngularVelocity(float x, float y, float z) : angularVelocity{x, y, z}, direction{0.f, 0.f, 0.f} {}
//    AngularVelocity(Magnum::Vector3 angularVelocity) : angularVelocity(angularVelocity), direction{0.f, 0.f, 0.f} {}

    Magnum::Vector3 angularVelocity;
    Magnum::Vector3 direction;
};

struct Player {};

struct AIDriven {};

struct Destroyable
{
    //Destroyable() : Destroyable(100,100) {}
//    Destroyable(int health) : health(health), maxHealth(health) {}
//    Destroyable(int health, int maxHealth) : health(health), maxHealth(maxHealth) {}
    
    int health;
    int maxHealth;
};

struct Score
{
//    Score(int score) : score(score) {}

    int score = 0;
};

struct Children
{
//    Children() : children{} {}
    
    std::map<std::string, entt::DefaultRegistry::entity_type> children;
};

struct LightComponent
{
    LightComponent() : light{nullptr} {}
    LightComponent(SceneNode* l) : light(l) {}
    
    SceneNode* light = nullptr;
};
