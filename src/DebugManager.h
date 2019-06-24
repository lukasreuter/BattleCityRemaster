/**
 @file      DebugManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

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
