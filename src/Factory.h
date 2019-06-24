/**
 @file      Factory.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Components.h"
#include "Registry.hpp"


class Factory
{
public:
    [[nodiscard]]
    static Entity createTank(Registry& where, std::string prefix, float velocity, float angularVelocity, const Magnum::Vector3& overHeating, int health, bool ai);

    [[nodiscard]]
    static Entity createBlock(Registry& where, int x, int y, int z, std::string material);

    static void createFloor(Registry& where, int sizex, int sizey, int repetition_x, int repetition_y, std::string material);

    [[nodiscard]]
    static Entity createProjectile(Registry& where, Magnum::Vector3 pos, Magnum::Quaternion ori, float velocity, std::string materialName);
};
