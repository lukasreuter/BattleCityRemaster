#pragma once

#include "Singleton.h"
#include "Registry.hpp"



class HeatingManager : public Singleton<HeatingManager>
{
public:
    void Update(float dt, Registry& registry);
};
