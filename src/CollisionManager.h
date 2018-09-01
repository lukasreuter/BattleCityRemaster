#pragma once

#include "Singleton.h"
#include "Components.h"
#include <string>

class CollisionManager : Singleton<CollisionManager>
{
public:
    static bool Collide(Position pos, Magnum::Vector3 delta, Orientation ori, std::string name);
};
