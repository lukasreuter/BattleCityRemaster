#include "HeatingManager.h"
#include "Components.h"


void HeatingManager::Update(float dt, entt::DefaultRegistry& registry)
{
    registry.view<OverHeating>(entt::raw_t{}).each([dt] (auto& overHeatingComp)
    {
        if (overHeatingComp.overheating < overHeatingComp.maxheating)
        {
            overHeatingComp.overheating += dt;
        }
    });
}
