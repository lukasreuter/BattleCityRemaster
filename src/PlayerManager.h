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
    //! @todo re-enable these
    /*void handleKeyPressed(const OIS::KeyEvent &event);
    void handleKeyReleased(const OIS::KeyEvent &event);
    void handleMouseMoved(const OIS::MouseEvent &event);
    void handleMousePressed(const OIS::MouseEvent &event, OIS::MouseButtonID id);
    void handleMouseReleased(const OIS::MouseEvent &event, OIS::MouseButtonID id);*/
private:
    Entity player;
    void fire();
};
