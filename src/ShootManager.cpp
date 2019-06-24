/**
 @file      ShootManager.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "ShootManager.h"
#include "RenderManager.h"
#include "Components.h"
#include "Messages.h"
#include "MessageManager.h"
#include "Factory.h"
#include "ScreenManager.h"
#include "EntityManager.h"
#include <iostream>

//ShootManager::ShootManager() noexcept
//{
//}


ShootManager::~ShootManager(){
    //delete mRaySceneQuery;
}


void ShootManager::init()
{
    MessageManager::GetRef().subscribe<ShootEvent>(this);
  //  mRaySceneQuery = RenderManager::getPtr()->getSceneManager()->createRayQuery(Ogre::Ray());
}

void ShootManager::receive(const ShootEvent &event)
{
    using namespace Magnum;

    auto start = event.start;
    auto bdirection =  event.bodyDirection;
    auto tdirection =  event.turretDirection;
    Magnum::Quaternion ori= bdirection.orientation * tdirection.orientation;
    //! @todo
//    Ogre::Ray ray(start->position, -(ori).zAxis());
//    mRaySceneQuery->setRay(ray);
//    Ogre::RaySceneQueryResult& result = mRaySceneQuery->execute();
//    Ogre::RaySceneQueryResult::iterator itr;
    long int min = 100000;
    std::string minName = "";
    /*
    for (itr = result.begin(); itr != result.end(); ++itr)
    {
        if (min > itr->distance && itr->distance > 0)
        {
            min = itr->distance;
            minName = itr->movable->getParentSceneNode()->getName();
        }
    }*/

    auto& reg = EntityManager::Registry();
    auto e = event.entity;

    std::string materialName = (reg.has<AI>(event.entity))
        ? "RedLaser"
        : "Laser";

    Factory::createProjectile(reg, start.position, ori, 600, materialName);
    std::cout << minName << std::endl;
    MessageManager::GetRef().emit<HitEvent>(minName, 100);
}
