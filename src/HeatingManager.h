#pragma once

#include <entity/registry.hpp>
#include "Singleton.h"


class HeatingManager : public Singleton<HeatingManager>
{
public:
    void Update(float dt, entt::DefaultRegistry& registry);
};
