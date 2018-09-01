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
