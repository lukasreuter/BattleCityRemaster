#include "MovementManager.h"
#include "Registry.hpp"
#include "CollisionManager.h"
#include "ScreenManager.h"
#include "MessageManager.h"
#include "Logger.h"


void MovementManager::Init(Registry& registry)
{
    registry.prepare_persistent_view<Position, Orientation>();
    
    LOGD("MovementManager configured")
}

void MovementManager::Update(float dt, Registry& registry)
{
    using namespace Magnum;
    
    Vector3 delta;
    
    registry.persistent_view<Position, Orientation>().each([&registry, &delta, dt] (auto entity, auto& pos, auto& ori)
    {
        std::string name = registry.get<Name>(entity).name;

        MessageManager::GetRef().emit<MoveEvent>(pos.position.x(), pos.position.y(), pos.position.z());
        
        if (registry.has<AngularVelocity>(entity))
        {
            const auto& angVel = registry.get<AngularVelocity>(entity);
            delta = angVel.angularVelocity * dt;
            Quaternion qx{ Vector3::xAxis(), static_cast<float>(Deg{ delta.x() }) };
            Quaternion qy{ Vector3::yAxis(), static_cast<float>(Deg{ delta.y() }) };
            Quaternion qz{ Vector3::zAxis(), static_cast<float>(Deg{ delta.z() }) };

            ori.orientation = ori.orientation * qx * qy * qz;
        }

        if (registry.has<Velocity>(entity))
        {
            const auto& vel = registry.get<Velocity>(entity);
            delta = vel.velocity * dt;
            delta = ori.orientation.transformVector(delta);
            //sposta se non ci sono collisioni

            bool collided = CollisionManager::Collide(pos, delta, ori, name);

            if (!collided) {
                pos.position += delta;
            } else if(name == "proiettile"){/*
                ptr<Renderable> rend = entity.component<Renderable>();

                Ogre::MovableObject* light = entity.component<LightComponent>()->light;
                RenderManager::getPtr()->getSceneManager()->destroyMovableObject(light);

                RenderManager::getPtr()->getSceneManager()->destroySceneNode(rend->sceneNode->getName());
                entity.destroy();
             */
            }
        }
    });
}
