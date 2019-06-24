/**
 @file      ParticleManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "MessageManager.h"
#include "Messages.h"
#include "Registry.hpp"
#include <string>
#include <entt.hpp>

struct Particle
{
    Particle(std::string name, std::string templateName)
    {/*
        partSys = RenderManager::getPtr()->getSceneManager()->createParticleSystem(name, templateName);
        partSys->getEmitter(0)->setEnabled(false);
        originalQuota = partSys->getParticleQuota();
        RenderManager::getPtr()->getSceneManager()->getRootSceneNode()->attachObject(partSys);
    */
    }

    //Ogre::ParticleSystem *partSys;
    size_t originalQuota;
};


class ParticleManager : public Singleton<ParticleManager>
{
public:
    void init();
    void ReceiveShootEvent(const ShootEvent &);
    void ReceiveObjectDestroyed(const ObjectDestroyed &);
    void Update(float dt);

private:
    void createEmitter(std::string name, Entity ent);

    const double deleteInterval = 5;
    double timeSinceLastDelete;
    std::map<std::string, Particle*> particleSystems;
    //std::vector<Ogre::ParticleEmitter*> emitters;
};
