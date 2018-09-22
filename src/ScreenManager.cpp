#include "ScreenManager.h"
#include "RenderManager.h"
#include "MessageManager.h"
//#include "entityx.h"


ScreenManager::~ScreenManager()
{
    while (!_screens.empty()) {
        _screens.back()->Leave();
        _screens.pop_back();
    }
}

void ScreenManager::Init(Screen *initialScreen)
{
    auto& messenger = MessageManager::GetRef();
    messenger.subscribe<KeyPressedEvent>(this);
    messenger.subscribe<KeyReleasedEvent>(this);
    messenger.subscribe<MouseMovedEvent>(this);
    messenger.subscribe<MousePressedEvent>(this);
    messenger.subscribe<MouseReleasedEvent>(this);
    //Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
    //pushScreen(initialScreen);
}

void ScreenManager::PopScreen()
{
    if (!_screens.empty()) {
        _screens.back()->Leave();
        _screens.pop_back();
    }

    if (!_screens.empty())
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
    if (!_screens.empty()) {
        _screens.back()->Update(dt);
    }
}

void ScreenManager::receive(const KeyPressedEvent &event)
{/*
    if(event.event.key == OIS::KC_SYSRQ)
        RenderManager::getPtr()->getRenderWindow()->writeContentsToTimestampedFile("Battlecity2014_",".png");

    if(!mScreens.empty()){
        mScreens.back()->keyPressed(event.event);
    }
*/
}

void ScreenManager::receive(const KeyReleasedEvent& event)
{
    if (!_screens.empty()) {
        _screens.back()->keyReleased(event);
    }
}

void ScreenManager::receive(const MouseMovedEvent &event)
{/*
    if(!mScreens.empty()){
       Screen* curr = mScreens.back();
       curr->mouseMoved(event.event);
    }
  */
}

void ScreenManager::receive(const MousePressedEvent &event)
{/*
    if(!mScreens.empty()){
        Screen* curr = mScreens.back();
        curr->mousePressed(event.event, event.buttonID);
    }
  */
}

void ScreenManager::receive(const MouseReleasedEvent &event)
{
    if(!_screens.empty()){
 //       mScreens.back()->mouseReleased(event.event, event.buttonID);
    }
}
