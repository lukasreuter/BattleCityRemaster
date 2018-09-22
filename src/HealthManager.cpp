#include "HealthManager.h"
#include "Components.h"
#include "MessageManager.h"
#include "Messages.h"
#include "ScreenManager.h"
#include "MapManager.h"
#include "EntityManager.h"
#include "Logger.h"
#include <iostream>
#include <string>


HealthManager::HealthManager() noexcept
{
    MessageManager::GetRef().subscribe<HitEvent>(this);

    LOGD(GREENBOLD << "HealthManager" << RESET << "configured")
}

HealthManager::~HealthManager()
{
    MessageManager::GetRef().unsubscribe<HitEvent>(this);

    LOGD(GREENBOLD << "HealthManager" << RESET << "shutdown")
}

void HealthManager::receive(const HitEvent& event)
{
    LOGD("ricevuto");
    auto& registry = EntityManager::Registry();
    
    //!@todo: replace the lambda with a loop or else the early return dont work as expected
    auto view = registry.view<Destroyable, Renderable, Name>();
    //.each([&registry, &event] (auto entity, auto& destroyable, auto& renderable, auto& entName)
    for (auto entity : view)
    {
        auto& destroyable = registry.get<Destroyable>(entity);
        auto& renderable = registry.get<Renderable>(entity);
        auto& entName = registry.get<Name>(entity);
        
        std::string name;

        if (entName.name != "Block")
        {
            auto& child = registry.get<Children>(entity);
            //! @todo
//            name = child.children["body"].component<Renderable>()->sceneNode->getName();
        } else {
//            ptr<Renderable> rend = entity.component<Renderable>();
            //! @todo
//            name = renderable.sceneNode->getName();
        }

        LOGD("name: " << name);

        int max = destroyable.maxHealth;

        if (name == event.targetName)
        {
            destroyable.health -= event.points;
            if (destroyable.health <= 0)
            {
                MessageManager::GetRef().emit<ObjectDestroyed>(entity);
                
//                if (entity.valid()) redundant as the entity is always valid when using a view
                {
                    auto& pos = registry.get<Position>(entity);
                    if (entName.name == "Block")
                    {
                        MapManager::GetRef().DeletePosition(pos.position);
//!@todo fix this                        RenderManager::GetRef().getSceneManager().destroySceneNode(renderable.sceneNode);
                        //!                        entity.destroy(); @todo: defer this to ouside the loop
                    } else {
                        pos.position = MapManager::GetRef().FindFreePos();
                        destroyable.health = max;
                        destroyable.maxHealth = max;
                    }
                }
                return;
            } else {
                LOGD("punti" << destroyable.health)
//                entity.assign<Destroyable>(points->health, max);
            }
            return;
        }
    }
}
