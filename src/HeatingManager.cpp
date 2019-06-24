/**
 @file      HeatingManager.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "HeatingManager.h"
#include "Components.h"


void HeatingManager::Update(float dt, Registry& registry)
{
    registry.raw_view<OverHeating>().each([dt] (auto& overHeatingComp)
    {
        if (overHeatingComp.overheating < overHeatingComp.maxheating)
        {
            overHeatingComp.overheating += dt;
        }
    });
}
