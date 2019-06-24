#include "ScreenManager.h"
#include "RenderManager.h"


ScreenManager::~ScreenManager()
{
    while (not _screens.empty()) {
        _screens.back()->Leave();
        _screens.pop_back();
    }
}

void ScreenManager::PopScreen()
{
    if (not _screens.empty()) {
        _screens.back()->Leave();
        _screens.pop_back();
    }

    if (not _screens.empty())
        _screens.back()->Resume();
}

/*
bool ScreenManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
    if(!mScreens.empty()){
        OgreBites::SdkTrayManager *tray = mScreens.back()->getTrayMgr();
        tray->frameRenderingQueued(evt);
        mScreens.back()->update(evt.timeSinceLastFrame);
    }
    return true;
}
*/

void ScreenManager::Update(float dt)
{
    if (not _screens.empty()) {
        _screens.back()->Update(dt);
    }
}

void ScreenManager::ReceiveKeyPressedEvent(const KeyPressedEvent& event)
{/* !@todo
    if(event.event.key == OIS::KC_SYSRQ)
        RenderManager::getPtr()->getRenderWindow()->writeContentsToTimestampedFile("Battlecity2014_",".png");

  */
    if (not _screens.empty()) {
        _screens.back()->keyPressed(event);
    }
}

void ScreenManager::ReceiveKeyReleasedEvent(const KeyReleasedEvent& event)
{
    if (not _screens.empty()) {
        _screens.back()->keyReleased(event);
    }
}

void ScreenManager::ReceiveMouseMovedEvent(const MouseMovedEvent& event)
{
    if (not _screens.empty()) {
       _screens.back()->mouseMoved(event);
    }
}

void ScreenManager::ReceiveMousePressedEvent(const MousePressedEvent& event)
{
    if (not _screens.empty()) {
        _screens.back()->mousePressed(event);
    }
}

void ScreenManager::ReceiveMouseReleasedEvent(const MouseReleasedEvent& event)
{
    if (not _screens.empty()) {
        _screens.back()->mouseReleased(event);
    }
}
