#include "HeatingManager.h"
#include "Components.h"


void HeatingManager::Update(float dt, Registry& registry)
{
    registry.raw_view<OverHeating>().each([dt] (auto& overHeatingComp)
    {
        if (overHeatingComp.overheating < overHeatingComp.maxheating)
        {
            overHeatingComp.overheating += dt;
        }
    });
}
