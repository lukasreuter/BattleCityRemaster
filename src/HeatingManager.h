#pragma once

#include "Singleton.h"
#include "ManagerInterface.h"


class HeatingManager : public Singleton<HeatingManager>
{
public:
    void Update(milliseconds dt, entt::DefaultRegistry& registry);
};
