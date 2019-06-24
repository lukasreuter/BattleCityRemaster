/**
 @file      ShootManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "Messages.h"
//#include "entityx.h"
//#include<Ogre.h>

class ShootManager : public Singleton<ShootManager>
{
public:
    ShootManager() = default;
    ~ShootManager();
    void init();
    void receive(const ShootEvent& event);

protected:
    //Ogre::RaySceneQuery* mRaySceneQuery;
};
