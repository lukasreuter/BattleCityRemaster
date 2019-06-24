/**
 @file      HealthManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"


class HealthManager : public Singleton<HealthManager>
{
public:
    HealthManager() noexcept;
    ~HealthManager();
    void receive(const struct HitEvent &event);

protected:
    //entityx::ptr<entityx::EntityManager> entities;
};
