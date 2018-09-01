#include "DebugManager.h"
#include "MessageManager.h"
#include "Logger.h"


void DebugManager::init()
{/*
    events->subscribe<KeyPressedEvent>(*this);
    logManager = Ogre::LogManager::getSingletonPtr();
    logManager->createLog("Battlecity.log",false,false,false);
  */
}

void DebugManager::receive(const KeyPressedEvent &event)
{
    auto keyName = Magnum::Platform::Sdl2Application::KeyEvent::keyName(event.key);
    
    LOGD("Premuto " << keyName)
}

void DebugManager::receive(const MoveEvent &event)
{
    LOGD(event.x << "\t" << event.y << "\t" << event.z)
}
