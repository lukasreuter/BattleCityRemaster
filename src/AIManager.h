#pragma once

#include <entt.hpp>
#include "Singleton.h"
#include "Messages.h"
#include "Components.h"
//#include "Ogre.h"

#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>


class AIManager : public Singleton<AIManager>
{
public:
    void init();
    void update(double dt);
/*
private:
    entt::::Entity tankPlayer;
    entityx::EventManager* events;

 */
    using Entity = entt::DefaultRegistry::entity_type;
    
    void seek(Velocity& vel,AngularVelocity& angVel,Orientation& ori, Magnum::Vector3 diff, Magnum::Rad theta, double dt);
    void walk(Velocity& vel,Orientation& ori,AngularVelocity& angVel,Position& pos, double dt);
    //void fire(entityx::Entity start, entityx::Entity end);
    void fire(Entity start, Entity end);

};
