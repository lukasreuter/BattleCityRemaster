#pragma once

#include "Singleton.h"


class MovementManager : public Singleton<MovementManager>
{
public:
    MovementManager();
    void init();
    void update(double dt);
};
