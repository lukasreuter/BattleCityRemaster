#pragma once

#include "Singleton.h"
#include "MessageManager.h"


class DebugManager : public Singleton<DebugManager>
{
public:
    DebugManager() noexcept;
    ~DebugManager();
    
    void ReceiveKeyPressedEvent(const KeyPressedEvent& event);
    //void receive(const KeyReleasedEvent& event);
    //void receive(const MouseMovedEvent& event);
    void ReceiveMoveEvent(const MoveEvent& event);
};
