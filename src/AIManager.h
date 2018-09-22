#pragma once

#include "Singleton.h"
#include "Components.h"
#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>
#include <entt.hpp>


class AIManager : public Singleton<AIManager>
{
    using Entity = entt::DefaultRegistry::entity_type;
    
public:
    void Init(entt::DefaultRegistry& registry);
    void Update(float dt, entt::DefaultRegistry& registry);
/*
private:
    entt::::Entity tankPlayer;
    entityx::EventManager* events;

 */
    
    void Seek(Velocity& vel, AngularVelocity& angVel, Orientation& ori, Magnum::Vector3 diff, Magnum::Rad theta, float dt);
    void Walk(Velocity& vel, Orientation& ori, AngularVelocity& angVel, Position& pos, double dt);
    void Fire(Entity start, Entity end);
};
