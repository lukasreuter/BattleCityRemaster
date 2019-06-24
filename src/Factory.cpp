#include "Factory.h"
#include "Components.h"
#include "DotSceneLoader.h"
#include "SceneManager.h"
#include <Magnum/Magnum.h>
#include <Magnum/Math/Quaternion.h>
#include <Magnum/SceneGraph/SceneGraph.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/SceneGraph/MatrixTransformation3D.h>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Drawable.h>
#include <string>


using Object3D = Magnum::SceneGraph::Object<Magnum::SceneGraph::MatrixTransformation3D>;
using Scene3D = Magnum::SceneGraph::Scene<Magnum::SceneGraph::MatrixTransformation3D>;


Entity Factory::createTank(Registry& registry, std::string prefix, float linearVelocity, float angularVelocity, const Magnum::Vector3& overHeating, int health, bool ai)
{
    using namespace Magnum;
    
    DotSceneLoader loader;
    auto& sceneMgr = SceneManager::GetRef();

    loader.parseDotScene("tank.scene", "General", sceneMgr, 0, prefix);
    
    auto* ctl    = sceneMgr.getSceneNode(prefix + "TankControl");
    auto* body   = sceneMgr.getSceneNode(prefix + "TankBody");
    auto* turret = sceneMgr.getSceneNode(prefix + "TankTurret");
    auto* cannon = sceneMgr.getSceneNode(prefix + "TankCannon");
    
    Entity tankEmptyControl = registry.create();
    Entity tankTurret = registry.create();
    Entity tankBody = registry.create();
    Entity tankCannon = registry.create();

    registry.assign<Position>(tankEmptyControl, ctl->transformation().translation());
    registry.assign<Orientation>(tankEmptyControl, Quaternion::fromMatrix(ctl->transformation().rotation()));
    registry.assign<Velocity>(tankEmptyControl, Vector3{ 0, 0, linearVelocity });
    registry.assign<AngularVelocity>(tankEmptyControl, Vector3{ 0, angularVelocity, 0 });
    registry.assign<Renderable>(tankEmptyControl, ctl);
    registry.assign<OverHeating>(tankEmptyControl, overHeating.x(), overHeating.y(), overHeating.z());
    registry.assign<Destroyable>(tankEmptyControl, health, health);
    registry.assign<Collidable>(tankEmptyControl);
    registry.assign<Name>(tankEmptyControl, prefix);
    
    if (ai)
    {
        registry.assign<AI>(tankEmptyControl);
        /*
        Ogre::Entity *model = static_cast<Ogre::Entity*>(body->children().first());
        model->getSubEntity(1)->setMaterialName("Red");

        model = static_cast<Ogre::Entity*>(turret->getAttachedObject(0));
        model->getSubEntity(1)->setMaterialName("Red");

        model = static_cast<Ogre::Entity*>(cannon->getAttachedObject(0));
        model->getSubEntity(1)->setMaterialName("Red");*/
    }

    auto& child = registry.assign<Children>(tankEmptyControl);
    child.children["body"]   = tankBody;
    child.children["turret"] = tankTurret;

    registry.assign<Position>(tankTurret, turret->transformation().translation());
    registry.assign<Orientation>(tankTurret, Quaternion::fromMatrix(turret->transformation().rotation()));
    registry.assign<Renderable>(tankTurret, turret);
    child = registry.assign<Children>(tankTurret);
    child.children["cannon"] = tankCannon;

    registry.assign<Position>(tankBody, body->transformation().translation());
    registry.assign<Orientation>(tankBody, Quaternion::fromMatrix(body->transformation().rotation()));
    registry.assign<Renderable>(tankBody, body);

    registry.assign<Position>(tankCannon, cannon->transformation().translation());
    registry.assign<Orientation>(tankCannon, Quaternion::fromMatrix(cannon->transformation().rotation()));
    registry.assign<Renderable>(tankCannon, cannon);

    ctl->scale(Vector3{ .35f, .55f, .35f });
    
    return tankEmptyControl;
}


Entity Factory::createBlock(Registry& registry, int x, int y, int z, std::string material)
{
    Entity block = registry.create();
    auto& sceneMgr = SceneManager::GetRef();
    /*
    Ogre::Entity* wall = sceneMgr->createEntity("Cube.mesh");
    wall->setMaterialName(material);
    Ogre::SceneNode* wallNode = sceneMgr->getRootSceneNode()->createChildSceneNode();

    wallNode->attachObject(wall);

    block.assign<Position>(x,y,z);
    wallNode->setPosition(x,y,z);
    block.assign<Orientation>(wallNode->getOrientation());
    block.assign<Renderable>(wallNode);
     */
    registry.assign<Name>(block, "Block");
    if (material == "Wall") {
        registry.assign<Destroyable>(block, 200, 200);
    }

    return block;
}


Entity Factory::createProjectile(Registry& where, Magnum::Vector3 pos, Magnum::Quaternion ori, float velocity, std::string materialName)
{/*
    Ogre::Entity *projMesh;
    Ogre::SceneManager *sceneMgr = RenderManager::getPtr()->getSceneManager();

    projMesh = sceneMgr->createEntity("ProjectileMesh.mesh");
    projMesh->setMaterialName(materialName);

    Entity proj = where->create();

    Ogre::SceneNode *projNode = sceneMgr->getRootSceneNode()->createChildSceneNode();
    projNode->attachObject(projMesh);

    Ogre::Light *light = sceneMgr->createLight();
    if(materialName == "RedLaser")
        light->setDiffuseColour(Ogre::ColourValue(.8, .2, .2));
    else
        light->setDiffuseColour(Ogre::ColourValue(.2, .2, .8));

    light->setType(Ogre::Light::LT_POINT);
    projNode->attachObject(light);



    projNode->setPosition(pos);
    projNode->setOrientation(ori);

    //projNode->translate(0, 0, -2, Ogre::SceneNode::TS_LOCAL);

    proj.assign<Position>(projNode->getPosition());
    proj.assign<Orientation>(ori);

    proj.assign<Velocity>(0, 0, velocity);
    proj.component<Velocity>()->direction.z = -1;
    proj.assign<Renderable>(projNode);
    proj.assign<AngularVelocity>(0, 0, 10);
    proj.assign<Name>("proiettile");
    proj.assign<LightComponent>(light);
    return proj;
  */
    return where.create();
}


void Factory::createFloor(Registry& entityMgr, int sizex, int sizey, int repetition_x, int repetition_y, std::string material)
{/*
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
    Ogre::MeshManager::getSingletonPtr()->createPlane("floorPlane",Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                      plane, sizex, sizey, 1, 1, true, 1, repetition_x, repetition_y, Ogre::Vector3::UNIT_Z);
    Ogre::SceneManager* sceneMgr = RenderManager::getPtr()->getSceneManager();

    Ogre::Entity* floorEntity = sceneMgr->createEntity("floorPlane");

    floorEntity->setMaterialName(material);

    sceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(floorEntity);
  */
}
