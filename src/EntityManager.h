//
//  EntityManager.h
//  BattleCity2018
//
//  Created by Lukas Reuter on 01.09.18.
//

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
