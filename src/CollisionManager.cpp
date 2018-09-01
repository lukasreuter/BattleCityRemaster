#include "CollisionManager.h"
#include "MapManager.h"


bool CollisionManager::Collide(Position pos, Magnum::Vector3 delta, Orientation ori, std::string name)
{/*
    MapManager* map = MapManager::getPtr();
    if (map->Collide(pos, delta, ori) != 0)
        return true;

    entityx::ptr<entityx::EntityManager> entities = ScreenManager::getPtr()->getCurrentEntities();

    for( auto entity : entities->entities_with_components<Position, Orientation, Velocity, AngularVelocity,Name>()){
        entityx::ptr<Position> pos0 = entity.component<Position>();
        std::string name0 = entity.component<Name>()->name;
        if (name0.compare(name) != 0){
            double dist = pos0->position.distance(pos.position + delta);
            if (dist < 1 && dist > 0)
                return true;
        }
    }

    return false;
  */
    return false;
}
