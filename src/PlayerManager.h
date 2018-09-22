#pragma once

#include <entt.hpp>
#include "Singleton.h"
#include "Messages.h"

//! @todo put thhis into a seperate header
typedef entt::DefaultRegistry::entity_type Entity;

class PlayerManager : public Singleton<PlayerManager>
{
public:
    void init();
    void setPlayerEntity(Entity player);
    Entity getPlayerEntity() const;
    
    void handleKeyPressed(const KeyPressedEvent& event);
    void handleKeyReleased(const KeyReleasedEvent& event);
    void handleMouseMoved(const MouseMovedEvent& event);
    void handleMousePressed(const MousePressedEvent& event);
    void handleMouseReleased(const MouseReleasedEvent& event);
    
private:
    Entity player;
    void fire();
};
