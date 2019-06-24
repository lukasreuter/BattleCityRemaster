#include "AIManager.h"
#include "MapManager.h"
#include "Logger.h"
#include "EntityManager.h"
#include "PlayerManager.h"
#include "MessageManager.h"
#include <iostream>


void AIManager::Init(Registry& registry)
{
    /// prepare the persistent view for the AI controlled entities
    registry.prepare_persistent_view<Position, AI, Orientation, Velocity, AngularVelocity>();

    LOGD(GREENBOLD << "AIManager" << RESET << "configured")
}

void AIManager::Update(float dt, Registry& registry)
{
    using namespace Magnum;
    constexpr int PlayerAIDistance = 36;
    
    auto player = PlayerManager::GetRef().GetPlayerEntity();
    
    //! @todo maybe remove this check and only execute the update when the player is there
    if (not registry.valid(player)) return;
    
    srand(time(0));
    const Position& playerPos = registry.get<Position>(player);
    static constexpr Rad oneDegree{ Deg{ 1 } };
        
    registry.persistent_view<Position, AI, Orientation, Velocity, AngularVelocity>().each([this, &playerPos, player, dt](auto entity, auto& pos, auto& /*ai*/, auto& ori, auto& velocity, auto& angular)
    {
        float dist = abs((playerPos.position - pos.position).length());
        Vector3 diff = pos.position - playerPos.position;
        
        Rad theta = Math::angle(ori.orientation.transformVector(Vector3::zAxis()).normalized(), diff.normalized());
        
        // if player is closer than this distance, try to chase it
        if (dist < 70 && theta > oneDegree)
        {
            Seek(velocity, angular, ori, diff, theta, dt);
            return;
        }

        // if the enemy is in range of the player and approx looking its direction
        if (dist < PlayerAIDistance && theta <= oneDegree)
        {
            Fire(entity, player);
            return;
        }

        if (dist > PlayerAIDistance)
        {
            Walk(velocity, angular, ori, pos, dt);
        }
    });
}

void AIManager::Seek(Velocity& vel, AngularVelocity& angleVel, const Orientation& ori, const Magnum::Vector3& diff, Magnum::Rad theta, float dt)
{
    using namespace Magnum;
    
    Quaternion qy{ Vector3::yAxis(), float(theta) * dt };
    
    if (Math::angle((ori.orientation * qy).transformVector(Vector3::zAxis()), diff.normalized()) > theta) {
        auto magnitude = angleVel.angularVelocity.length();
        angleVel.angularVelocity = Vector3{ -1 }.normalized() * magnitude;
    } else {
        auto magnitude = angleVel.angularVelocity.length();
        angleVel.angularVelocity = Vector3{ 1 }.normalized() * magnitude;
    }
    vel.velocity.z() = 0;
}

void AIManager::Walk(Velocity& vel, AngularVelocity& angVel, const Orientation& ori, const Position& pos, double dt)
{
    using namespace Magnum;
    
    Vector3 backVector{ 0, 0, -1 };
    Vector3 delta = ori.orientation.transformVector((vel.velocity * backVector) * dt);
    Vector3 delta10 = ori.orientation.transformVector(((vel.velocity * 10) * backVector) * dt);
    const MapManager& map = MapManager::GetRef();

    //std::cout<<map->collide(*(pos.get()),delta,*(ori.get()),"haha")<<std::endl;
    if ((map.Collide(pos, delta, ori) == 0) && (map.Collide(pos, delta10, ori) == 0))
    {
        auto magnitude = vel.velocity.length();
        vel.velocity = Vector3{ 0, 0, -1 }.normalized() * magnitude;
      //  angVel->direction=Ogre::Vector3(0,0,0);

        if (rand() % 1000 < 10)
        {
            int dir = rand() % 2;
            if (dir == 0) {
                dir = -1;
            }
            if (angVel.angularVelocity.y() == 0) {
                angVel.angularVelocity.y() = dir;
            }
        }
        return;
    }
    
    if (angVel.angularVelocity.y() == 0.f)
    {
        vel.velocity = Vector3{ 0, 0, 0 };
        
        int dir = rand() % 10;
        dir = (dir < 5) ? -1 : 1;

        angVel.angularVelocity.y() = static_cast<float>(dir);
    }
}

void AIManager::Fire(Entity start, Entity)
{
    //! @todo check if the entities have all the required components
    
    auto& registry = EntityManager::Registry();
    if (not registry.has<OverHeating>(start)) return;
    
    auto& overH = registry.get<OverHeating>(start);
    if (registry.has<Velocity, AngularVelocity>(start)) {
        registry.get<Velocity>(start).velocity.z() = 0;
        registry.get<AngularVelocity>(start).angularVelocity.y() = 0;
    }
    
    if (overH.overheating <= 0) {
        return;
    } else {
        overH.overheating -= overH.shootHeating;
        auto& pos = registry.get<Position>(start);
        auto& ori = registry.get<Orientation>(start);
        auto& children = registry.get<Children>(start);
        auto& turret = registry.get<Orientation>(children.children["turret"]);
        
        MessageManager::GetRef().emit<ShootEvent>(start, pos, ori, turret, "Player");
    }
    
    auto Success = MapManager::GetRef().FireCollision(registry.get<Position>(start), registry.get<Orientation>(start), "PlayerTankBody");
    if (Success)
    {
        std::cout << "Hit Player!" << std::endl;
    }
    return;
}
