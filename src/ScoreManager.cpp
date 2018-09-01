#include "ScoreManager.h"
#include "PlayerManager.h"
#include "ScreenManager.h"
#include "Screen.h"
#include <entt.hpp>


ScoreManager::ScoreManager() noexcept
{
    MessageManager::GetRef().subscribe<ObjectDestroyed>(this);
}

ScoreManager::~ScoreManager()
{
    MessageManager::GetRef().unsubscribe<ObjectDestroyed>(this);
}

void ScoreManager::receive(const ObjectDestroyed& event)
{
    entt::DefaultRegistry reg{};
    auto de = reg.create();
    
    Entity obj = event.object;
    /*if(obj == PlayerManager::GetRef().getPlayerEntity())
        ScreenManager::getPtr()->resetTo(GameOverScreen::getPtr());
    else if(obj.component<Name>()->name != "Block")
    {
        score += unitScore;
    }*/
}


