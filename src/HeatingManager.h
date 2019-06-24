/**
 @file      HeatingManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "Registry.hpp"



class HeatingManager : public Singleton<HeatingManager>
{
public:
    void Update(float dt, Registry& registry);
};
