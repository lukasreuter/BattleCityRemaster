//
//  EntityManager.h
//  BattleCity2018
//
//  Created by Lukas Reuter on 01.09.18.
//

#pragma once

#include "Singleton.h"
#include <entt.hpp>

class EntityManager : public Singleton<EntityManager>
{
    entt::DefaultRegistry _registry;
    
public:
    EntityManager() : _registry{} {}
    
    inline entt::DefaultRegistry& GetRegistry() { return _registry; };
    
    // short hand for GetRef().GetRegistry()
    static entt::DefaultRegistry& Registry() { return GetRef().GetRegistry(); };
};
