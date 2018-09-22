#include "ScoreManager.h"
#include "Logger.h"
#include "EntityManager.h"
#include "ScreenManager.h"


ScoreManager::ScoreManager() noexcept
{
    MessageManager::GetRef().subscribe<ObjectDestroyed>(this);

    LOGD(GREENBOLD << "ScoreManager" << RESET << " configured")
}

ScoreManager::~ScoreManager()
{
    MessageManager::GetRef().unsubscribe<ObjectDestroyed>(this);

    LOGD(GREENBOLD << "ScoreManager" << RESET << " teardown")
}

void ScoreManager::receive(const ObjectDestroyed& event)
{
    auto& reg = EntityManager::Registry();
    
    Entity obj = event.object;
    Entity player = reg.attachee<Player>();

    if (obj == player) {
        ScreenManager::GetRef().ResetTo<GameOverScreen>();
    } else if (auto name = reg.has<Name>() ? reg.get<Name>().name : ""; name != "Block") {
        score += unitScore;
    }
}


