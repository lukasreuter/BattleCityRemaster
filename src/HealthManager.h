#pragma once

#include "Singleton.h"
#include "Messages.h"


class HealthManager : public Singleton<HealthManager>
{
public:
    void init();
    void receive(const HitEvent &event);

protected:
    //entityx::ptr<entityx::EntityManager> entities;
};
