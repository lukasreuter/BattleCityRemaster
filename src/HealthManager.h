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
