/**
 @file      DebugManager.cpp
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include "DebugManager.h"
#include "Logger.h"


DebugManager::DebugManager() noexcept
{
#ifdef DEBUG_INPUT
    /// only activate the debugging features when actually in a debug build
    auto& dispatcher = MessageManager::GetRef().GetDispatcher();
    dispatcher.sink<MoveEvent>().connect<&DebugManager::ReceiveMoveEvent>(this);
    dispatcher.sink<KeyPressedEvent>().connect<&DebugManager::ReceiveKeyPressedEvent>(this);

    LOGD("DebugManager configured")
#endif
}

DebugManager::~DebugManager()
{
#ifdef DEBUG_INPUT
    auto& messenger = MessageManager::GetRef();
    messenger.unsubscribe<KeyPressedEvent>(this);
    messenger.unsubscribe<MoveEvent>(this);

    LOGD("DebugManager destroyed")
#endif
}

void DebugManager::ReceiveKeyPressedEvent(const KeyPressedEvent& event)
{
    auto keyName = Magnum::Platform::Sdl2Application::KeyEvent::keyName(event.key);

    LOGD("Pressed: " << keyName)
}

void DebugManager::ReceiveMoveEvent(const MoveEvent& event)
{
    LOGD(event.x << "\t" << event.y << "\t" << event.z)
}
