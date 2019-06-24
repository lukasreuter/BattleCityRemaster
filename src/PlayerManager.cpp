#include "PlayerManager.h"
#include "MessageManager.h"
#include "MapManager.h"
#include "Components.h"
#include "EntityManager.h"
#include <sstream>
//#include <OIS.h>
#include <entt.hpp>

void PlayerManager::init()
{
//    EntityManager::GetRegistry().
    
//    this->player =
}

void PlayerManager::SetPlayerEntity(Entity player)
{
    this->player = player;
}

Entity PlayerManager::GetPlayerEntity() const
{
    return player;
}

void PlayerManager::handleKeyPressed(const KeyPressedEvent& event)
{
    /*
    if(player.valid()){
        ptr<Velocity> vel = player.component<Velocity>();
        ptr<AngularVelocity> aVel = player.component<AngularVelocity>();

        switch(event.key)
        {
        case OIS::KC_W:
            vel->direction.z -= 1;
            break;
        case OIS::KC_S:
            vel->direction.z += 1;
            break;
        case OIS::KC_A:
            aVel->direction.y += 1;
            break;
        case OIS::KC_D:
            aVel->direction.y -= 1;
            break;
        }
    }
     */
}

void PlayerManager::handleKeyReleased(const KeyReleasedEvent& event)
{
    /*
    if(player.valid()){
        ptr<Velocity> vel = player.component<Velocity>();
        ptr<AngularVelocity> aVel = player.component<AngularVelocity>();
        switch(event.key)
        {
        case OIS::KC_W:
            vel->direction.z += 1;
            break;
        case OIS::KC_S:
            vel->direction.z -= 1;
            break;
        case OIS::KC_A:
            aVel->direction.y -= 1;
            break;
        case OIS::KC_D:
            aVel->direction.y += 1;
            break;
        }
    }
     */
}

void PlayerManager::handleMouseMoved(const MouseMovedEvent& event)
{
    /*
    if(player.valid()){
        // Body and turret orientation components
        ptr<Orientation> bodyOri, ori;

        Ogre::Quaternion rotation;
        Ogre::Quaternion newOri;
        Ogre::Vector3 axis;
        Ogre::Radian angle;

        // quaternions for the turrent and the cannon
        Ogre::Quaternion qy(Ogre::Degree(-event.state.X.rel * .05), Ogre::Vector3::UNIT_Y);
        //Ogre::Quaternion qx(Ogre::Degree(-event.state.Y.rel * .05), Ogre::Vector3::UNIT_X);

        // recovery of the necessary entities and components
        Entity turret= player.component<Children>()->children["turret"];
        //Entity cannon = turret.component<Children>()->children["cannon"];

        bodyOri = player.component<Children>()->children["body"].component<Orientation>();

        ori = turret.component<Orientation>();


        // calculate the new turret orientation

        newOri = ori->orientation * qy;
        // rotation of bodyOri and ori = bodyOri^-1 * ori
        rotation = bodyOri->orientation.Inverse() * newOri;
        rotation.ToAngleAxis(angle, axis);

        // if it is between -30 and +30 degrees, rotate the turret
        if(Ogre::Math::Abs(angle.valueDegrees()) < 75)
        {
            ori->orientation = newOri;
        }

        // Rotate the cannon

        //ori = cannon.component<Orientation>();
        //ori->orientation = ori->orientation * qx;
    }
     */
}

void PlayerManager::handleMousePressed(const MousePressedEvent& event)
{
    
}

void PlayerManager::handleMouseReleased(const MouseReleasedEvent& event)
{
    /*
    if(player.valid() && id == OIS::MB_Left)
        fire();
     */
}

void PlayerManager::fire()
{/*
    ptr<OverHeating> overH = player.component<OverHeating>();
    if(overH->overheating<=0)
        return;
    else {
        player.assign<OverHeating>(overH->overheating-overH->shootHeating,overH->shootHeating,overH->maxheating);

        //ptr<Orientation> oriP = player.component<Orientation>();
       //ori->orientation=
       // Ogre::Quaternion quat(oriP->orientation*player.component<Children>()->children["turret"].component<Orientation>()->orientation);
        //ptr<Orientation> ori;
        //ori.

        MessageManager::getPtr()->emit<ShootEvent>(player,player.component<Position>(),player.component<Orientation>(),player.component<Children>()->children["turret"].component<Orientation>(),"CPU");

    }// if(MapManager::getPtr()->fireCollision(start.component<Position>(),start.component<Orientation>(),"PlayerTankBody"))
   //     std::cout<<"Colpito!"<<std::endl;
    return;
  */
}
