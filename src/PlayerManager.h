#pragma once

#include <entt.hpp>
#include "Singleton.h"
#include "Messages.h"


class PlayerManager : public Singleton<PlayerManager>
{
public:
    void init();
    void SetPlayerEntity(Entity player);
    Entity GetPlayerEntity() const;
    
    inline static Entity GetPlayer() noexcept { return GetRef().GetPlayerEntity(); };
    
    void handleKeyPressed(const KeyPressedEvent& event);
    void handleKeyReleased(const KeyReleasedEvent& event);
    void handleMouseMoved(const MouseMovedEvent& event);
    void handleMousePressed(const MousePressedEvent& event);
    void handleMouseReleased(const MouseReleasedEvent& event);
    
private:
    entt::monostate<"Player"_hs> player{}; // ensures thread safety
    //Entity player;
    void fire();
};
