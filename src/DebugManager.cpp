#include "DebugManager.h"
#include "MessageManager.h"
#include "Logger.h"


DebugManager::DebugManager() noexcept
{
#ifdef DEBUG_INPUT
    /// only activate the debugging features when actually in a debug build
    auto& messenger = MessageManager::GetRef();
    messenger.subscribe<KeyPressedEvent>(this);
    messenger.subscribe<MoveEvent>(this);
    
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

void DebugManager::receive(const KeyPressedEvent &event)
{
    auto keyName = Magnum::Platform::Sdl2Application::KeyEvent::keyName(event.key);
    
    LOGD("Pressed: " << keyName)
}

void DebugManager::receive(const MoveEvent &event)
{
    LOGD(event.x << "\t" << event.y << "\t" << event.z)
}
