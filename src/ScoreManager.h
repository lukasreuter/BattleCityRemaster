#pragma once

#include "MessageManager.h"
#include "Singleton.h"
#include <entt.hpp>


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
