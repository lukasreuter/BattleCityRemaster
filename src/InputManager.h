/**
 @file      InputManager.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Singleton.h"
#include "RenderManager.h"
#include <Magnum/Platform/Sdl2Application.h>

typedef Magnum::Platform::Sdl2Application::KeyEvent KeyEvent;
typedef Magnum::Platform::Sdl2Application::MouseEvent MouseEvent;
typedef Magnum::Platform::Sdl2Application::MouseMoveEvent MouseMoveEvent;


class InputManager : public Singleton<InputManager>
{
public:
    InputManager();

    void keyPressed(const KeyEvent& arg);
    void keyReleased(const KeyEvent& arg);
    void mouseMoved(MouseMoveEvent& arg);
    void mousePressed(MouseEvent& arg);
    void mouseReleased(MouseEvent& arg);
};
