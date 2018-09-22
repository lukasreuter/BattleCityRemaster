#pragma once

#include "Singleton.h"
#include "Components.h"
#include <string>

class CollisionManager : public Singleton<CollisionManager>
{
public:
    static bool Collide(const Position& pos, const Magnum::Vector3& delta, const Orientation& ori, std::string name);
};
