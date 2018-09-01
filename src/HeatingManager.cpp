#include "HeatingManager.h"
#include "Components.h"


void HeatingManager::Update(float dt, entt::DefaultRegistry& registry)
{
    registry.view<OverHeating>().each([dt](auto entity, auto& overHeatingComp) {
        if (overHeatingComp.overheating < overHeatingComp.maxheating){
            overHeatingComp.overheating += dt;
        }
    });
}
