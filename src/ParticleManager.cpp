#include "ParticleManager.h"
#include "RenderManager.h"
#include "EntityManager.h"
//#include "Ogre.h"


void ParticleManager::init()
{
    auto& messenger = MessageManager::GetRef();
    auto& d = messenger.GetDispatcher();
    d.sink<ShootEvent>().connect<&ParticleManager::ReceiveShootEvent>(this);
    d.sink<ObjectDestroyed>().connect<&ParticleManager::ReceiveObjectDestroyed>(this);
    //messenger.subscribe<ShootEvent>(this);
    //messenger.subscribe<ObjectDestroyed>(this);
    timeSinceLastDelete = 0;
    /*
    particleSystems["explosion"] = new Particle("explosion","Supernova");
    */
}

void ParticleManager::ReceiveShootEvent(const ShootEvent &evt)
{/*
    if(evt.entity.valid())
    {
        entityx::Entity obj = evt.entity;

        //TODO Bullet
    }
  */
}

void ParticleManager::ReceiveObjectDestroyed(const ObjectDestroyed& evt)
{
    const auto& registry = EntityManager::Registry();
    
    if (registry.valid(evt.object))
    {
        createEmitter("explosion", evt.object);
    }
}

void ParticleManager::Update(float dt)
{
    timeSinceLastDelete += dt;
    /*
    if (timeSinceLastDelete >= deleteInterval && !emitters.empty())
    {
        Ogre::ParticleEmitter *pe = emitters.front();

        delete pe;
        pe = 0;
        emitters.erase(emitters.begin());
        timeSinceLastDelete = 0;
    }
    */
}

void ParticleManager::createEmitter(std::string name, Entity ent)
{/*
    if(ent.valid())
    {
        Particle *part = particleSystems[name];
        Ogre::ParticleEmitter *pe = part->partSys->addEmitter("Point");
        part->partSys->getEmitter(0)->copyParametersTo(pe);
        entityx::ptr<Position> pos = ent.component<Position>();
        pe->setPosition(pos->position);
        //emitters.push_back(pe);
        part->partSys->setParticleQuota(part->originalQuota + part->partSys->getParticleQuota());
    }*/
}
