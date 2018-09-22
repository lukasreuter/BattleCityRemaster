#include "CollisionManager.h"
#include "MapManager.h"
#include "EntityManager.h"


bool CollisionManager::Collide(const Position& pos, const Magnum::Vector3& delta, const Orientation& ori, std::string name)
{
    auto& map = MapManager::GetRef();
    if (map.Collide(pos, delta, ori) != 0)
        return true;
    
    auto& registry = EntityManager::Registry();
    
    auto view = registry.view<Position, Orientation, Velocity, AngularVelocity, Name>();
    
    for (auto entity : view)
    {
        auto& pos0 = registry.get<Position>(entity);
        auto& name0 = registry.get<Name>(entity).name;
        if (name0 != name)
        {
            double dist = (pos0.position - (pos.position + delta)).length();
            if (dist < 1 && dist > 0)
                return true;
        }
    }

    return false;
}
