/**
 @file      ManagerInterface.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include <entt.hpp>

typedef float milliseconds;

class ManagerInterface
{
public:
    virtual ~ManagerInterface();
    virtual void Init() = 0;
    virtual void Update(milliseconds dt, entt::DefaultRegistry& registry) = 0;
};
