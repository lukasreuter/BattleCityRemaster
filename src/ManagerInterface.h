//
//  ManagerInterface.h
//  BattleCity2018
//
//  Created by Lukas Reuter on 27.08.18.
//
#pragma once

#include <entt.hpp>

typedef float milliseconds;

class ManagerInterface
{
public:
    virtual void Init() = 0;
    virtual void Update(milliseconds dt, entt::DefaultRegistry& registry) = 0;
};
