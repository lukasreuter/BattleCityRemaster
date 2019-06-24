/**
 @file      ScoreManager.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "ScoreManager.h"
#include "Logger.h"
#include "EntityManager.h"
#include "PlayerManager.h"
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

    auto obj = event.object;
    auto player = PlayerManager::GetPlayer();

    if (obj == player) {
        ScreenManager::GetRef().ResetTo<GameOverScreen>();
    } else if (auto name = reg.has<Name>(obj) ? reg.get<Name>(obj).name : ""; name != "Block") {
        score += unitScore;
    }
}


