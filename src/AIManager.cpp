#include "AIManager.h"
#include "MapManager.h"
#include "Logger.h"
#include "EntityManager.h"
#include "MessageManager.h"


void AIManager::Init(entt::DefaultRegistry& registry)
{
    using namespace Magnum;
    
    /// prepare the persistent view for the AI controlled entities
    registry.prepare<Position, AI, Orientation, Velocity, AngularVelocity>();

    LOGD(GREENBOLD << "AIManager" << RESET << "configured")
}

void AIManager::Update(float dt, entt::DefaultRegistry& registry)
{
    using namespace Magnum;
    constexpr int PlayerAIDistance = 36;
    
    //! @todo maybe remove this check and only execute the update when the player is there
    if (!registry.has<Player>()) return;
    
    srand(time(0));
    auto player = registry.attachee<Player>();
    const Position& playerPos = registry.get<Position>(player);
    static constexpr Rad oneDegree{Deg{1}};
        
    registry.view<Position, AI, Orientation, Velocity, AngularVelocity>(entt::persistent_t{}).each([this, &playerPos, player, dt](auto entity, auto& pos, auto& ai, auto& ori, auto& velocity, auto& angular)
    {
        float dist = (playerPos.position - pos.position).length();
        Vector3 diff = pos.position - playerPos.position;
        
        Rad theta = Math::angle(ori.orientation.transformVector(Vector3::zAxis()).normalized(), diff.normalized());
        
        //se la distanza dal nemico è < di una soglia data e il nemico non è sotto tiro
        //punta il nemico

        if (abs(dist) < 70 && theta > oneDegree)
        {
            Seek(velocity, angular, ori, diff, theta, dt);
//            return;
        }

        //se il nemico è sottotiro spara
        if (abs(dist) < PlayerAIDistance && theta <= oneDegree)
        {
            Fire(entity, player);
            return;
        }

        if (abs(dist) > PlayerAIDistance) {
            Walk(velocity, ori, angular, pos, dt);
        }
    });
}

void AIManager::Seek(Velocity& vel, AngularVelocity& angleVel, Orientation& ori, Magnum::Vector3 diff, Magnum::Rad theta, float dt)
{
    using namespace Magnum;
    
    Quaternion qy{Vector3::yAxis(), float(theta) * dt};
    
    if(Math::angle((ori.orientation * qy).transformVector(Vector3::zAxis()), diff.normalized()) > theta)
        angleVel.direction = Vector3{-1};
    else
        angleVel.direction = Vector3{1};
    vel.direction.z() = 0;
}

void AIManager::Walk(Velocity& vel, Orientation& ori, AngularVelocity& angVel, Position& pos, double dt)
{
    using namespace Magnum;
    
    Vector3 backVector{0, 0, -1};
    Vector3 delta = ori.orientation.transformVector((vel.velocity * backVector) * dt);
    Vector3 delta10 = ori.orientation.transformVector(((vel.velocity * 10) * backVector) * dt);
    const MapManager& map = MapManager::GetRef();

    //std::cout<<map->collide(*(pos.get()),delta,*(ori.get()),"haha")<<std::endl;
    if ((map.Collide(pos, delta, ori) == 0) && (map.Collide(pos, delta10, ori) == 0))
    {
        vel.direction = Vector3{0, 0, -1};
      //  angVel->direction=Ogre::Vector3(0,0,0);

        if (rand() % 1000 < 10)
        {
            int dir = rand() % 2;
            if (dir == 0)
                dir = -1;
            if (angVel.direction.y() == 0)
                angVel.direction.y() = dir;
        }
        return;
    }
    if (angVel.direction.y() == 0)
    {
        vel.direction = Vector3{0, 0, 0};

        int dir = rand() % 10;
        dir = (dir < 5) ? -1 : 1;

        angVel.direction.y() = dir;
    }
}

void AIManager::Fire(Entity start, Entity end)
{
    //! @todo check if the entities have all the required components
    
    auto& registry = EntityManager::Registry();
    if (!registry.has<OverHeating>(start)) return;
    
    auto& overH = registry.get<OverHeating>(start);
    registry.get<Velocity>(start).direction.z() = 0;
    registry.get<AngularVelocity>(start).direction.y() = 0;
    
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
    // if(MapManager::getPtr()->fireCollision(start.component<Position>(),start.component<Orientation>(),"PlayerTankBody"))
   //     std::cout<<"Colpito!"<<std::endl;
    return;
}
