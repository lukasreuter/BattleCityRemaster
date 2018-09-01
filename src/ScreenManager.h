#pragma once

#include "Screen.h"
//#include <Ogre.h>
#include "Messages.h"
#include "Singleton.h"
#include <entt.hpp>
#include <vector>


class ScreenManager : /*public entityx::Receiver<ScreenManager>, */public Singleton<ScreenManager>//, public Ogre::FrameListener
{
public:
    ScreenManager() = default;
    ~ScreenManager();

    void init(Screen* initialScreen);


    void pushScreen(Screen* screen);
    void popScreen();
    void changeScreen(Screen* screen);
    void resetTo(Screen* screen);

    void update(double dt);

    //bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    //entityx::ptr<entityx::EntityManager> getCurrentEntities();
    
    entt::DefaultRegistry& GetEntityRegistry() const;

    void receive(const KeyPressedEvent& event);
    void receive(const KeyReleasedEvent& event);
    void receive(const MouseMovedEvent& event);
    void receive(const MousePressedEvent& event);
    void receive(const MouseReleasedEvent& event);

private:
    std::vector<Screen*> mScreens;
};
