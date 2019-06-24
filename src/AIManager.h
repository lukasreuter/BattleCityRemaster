#pragma once

#include "Singleton.h"
#include "Components.h"
#include "Registry.hpp"
#include <Magnum/Magnum.h>
#include <Magnum/Math/Vector3.h>
#include <entt.hpp>


class AIManager : public Singleton<AIManager>
{
public:
    void Init(Registry& registry);
    void Update(float dt, Registry& registry);
/*
private:
    entt::::Entity tankPlayer;
    entityx::EventManager* events;

 */
    
    void Seek(Velocity& vel, AngularVelocity& angVel, const Orientation& ori, const Magnum::Vector3& diff, Magnum::Rad theta, float dt);
    void Walk(Velocity& vel, AngularVelocity& angVel, const Orientation& ori, const Position& pos, double dt);
    void Fire(Entity start, Entity end);
};
