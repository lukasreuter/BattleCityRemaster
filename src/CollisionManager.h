/**
 @file      CollisionManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "Components.h"
#include <string>

class CollisionManager : public Singleton<CollisionManager>
{
public:
    static bool Collide(const Position& pos, const Magnum::Vector3& delta, const Orientation& ori, std::string name);
};
