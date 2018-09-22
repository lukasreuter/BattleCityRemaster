#include "ParticleManager.h"
#include "RenderManager.h"
//#include "Ogre.h"

ParticleManager::ParticleManager()
{
}


void ParticleManager::init()
{
    auto& messenger = MessageManager::GetRef();
    messenger.subscribe<ShootEvent>(this);
    messenger.subscribe<ObjectDestroyed>(this);
    
    /*
    MessageManager::getPtr()->subscribe<ShootEvent>(*this);
    MessageManager::getPtr()->subscribe<ObjectDestroyed>(*this);
    timeSinceLastDelete = 0;
    particleSystems["explosion"] = new Particle("explosion","Supernova");
  */
}

void ParticleManager::receive(const ShootEvent &evt)
{/*
    if(evt.entity.valid())
    {
        entityx::Entity obj = evt.entity;

        //TODO Bullet
    }
  */
}

void ParticleManager::receive(const ObjectDestroyed &evt)
{/*
    if(evt.object.valid())
    {
        entityx::Entity obj = evt.object;
        createEmitter("explosion", obj);
    }
  */
}

void ParticleManager::Update(float dt)
{
    /*
    timeSinceLastDelete += dt;
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

void ParticleManager::createEmitter(std::string name, entt::DefaultRegistry::entity_type ent)
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
