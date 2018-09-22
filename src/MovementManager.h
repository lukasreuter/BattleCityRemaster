#pragma once

#include <entity/registry.hpp>
#include "Singleton.h"


class MovementManager : public Singleton<MovementManager>
{
public:
    void Init(entt::DefaultRegistry& registry);
    void Update(float dt, entt::DefaultRegistry& registry);
};
