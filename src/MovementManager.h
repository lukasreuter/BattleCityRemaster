#pragma once

#include "Singleton.h"
#include "Registry.hpp"


class MovementManager : public Singleton<MovementManager>
{
public:
    void Init(Registry& registry);
    void Update(float dt, Registry& registry);
};
