/**
 @file      ScoreManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "MessageManager.h"
#include "Singleton.h"


class ScoreManager : public Singleton<ScoreManager>
{
public:
    ScoreManager() noexcept;
    ~ScoreManager();

    void Init() {};
    void receive(const ObjectDestroyed& event);

    inline int GetScore() const { return score; };
    inline void ResetScore() { score = 0; };

private:
    static constexpr int unitScore = 10;
    int score = 0;
    std::map<std::string, int> ranking;
};
