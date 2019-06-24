/**
 @file      EntityManager.h
 @author    Lukas Reuter
 @date      22.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "Registry.hpp"
#include <entt.hpp>

class EntityManager : public Singleton<EntityManager>
{
    Registry _registry;

public:
    EntityManager() : _registry{} {}

    inline Registry& GetRegistry() { return _registry; };

    // short hand for GetRef().GetRegistry()
    static Registry& Registry() { return GetRef().GetRegistry(); };
};
