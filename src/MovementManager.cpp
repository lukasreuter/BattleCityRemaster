#include "MovementManager.h"
#include "CollisionManager.h"
#include "ScreenManager.h"
#include "MessageManager.h"
#include "Logger.h"


void MovementManager::Init(entt::DefaultRegistry& registry)
{
    registry.prepare<Position, Orientation>();
    
    LOGD("MovementManager configured")
}

void MovementManager::Update(float dt, entt::DefaultRegistry& registry)
{
    using namespace Magnum;
    
    Vector3 delta;
    
    registry.view<Position, Orientation>(entt::persistent_t{}).each([&registry, &delta, dt] (auto entity, auto& pos, auto& ori)
    {
        std::string name = registry.get<Name>(entity).name;

        MessageManager::GetRef().emit<MoveEvent>(pos.position.x(), pos.position.y(), pos.position.z());
        
        if (registry.has<AngularVelocity>())
        {
            const auto& angVel = registry.get<AngularVelocity>(entity);
            delta = (angVel.angularVelocity * angVel.direction) * dt;
            Quaternion qx{Vector3::xAxis(), float(Deg{delta.x()})};
            Quaternion qy{Vector3::yAxis(), float(Deg{delta.y()})};
            Quaternion qz{Vector3::zAxis(), float(Deg{delta.z()})};

            ori.orientation = ori.orientation * qx * qy * qz;
        }

        if (registry.has<Velocity>(entity))
        {
            const auto& vel = registry.get<Velocity>(entity);
            delta = (vel.velocity * vel.direction) * dt;
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
