#ifndef PARTICLEMANAGER_H
#define PARTICLEMANAGER_H
#include "Singleton.h"
//#include "entityx.h"
#include "MessageManager.h"
#include "Messages.h"
#include <string>
#include <entt.hpp>

struct Particle{
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

class ParticleManager : public Singleton<ParticleManager>//, public entityx::Receiver<ParticleManager>
{
public:
    ParticleManager();
    void init();
    void receive(const ShootEvent &);
    void receive(const ObjectDestroyed &);
    void update(double dt);
private:
    void createEmitter(std::string name, entt::DefaultRegistry::entity_type ent);

    const double deleteInterval = 5;
    double timeSinceLastDelete;
    std::map<std::string, Particle*> particleSystems;
    //std::vector<Ogre::ParticleEmitter*> emitters;
};

#endif // PARTICLEMANAGER_H
