/**
 @file      Messages.h
 @author    Lukas Reuter
 @date      01.09.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#pragma once

#include "Components.h"
#include <Magnum/Platform/Sdl2Application.h>
#include <entt.hpp>
#include <string>

typedef Magnum::Platform::Sdl2Application::KeyEvent KeyEvent;
typedef Magnum::Platform::Sdl2Application::MouseEvent MouseEvent;
typedef Magnum::Platform::Sdl2Application::MouseMoveEvent MouseMoveEvent;

struct HitEvent
{
    std::string targetName;
    int points;
};

struct ShootEvent
{
    Entity entity;
    Position start;
    Orientation bodyDirection;
    Orientation turretDirection;
    std::string target;
};

struct KeyPressedEvent
{
    Magnum::Platform::Sdl2Application::KeyEvent::Key key;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    bool isRepeating = false;
};

struct KeyReleasedEvent
{
    Magnum::Platform::Sdl2Application::KeyEvent::Key key;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    bool isRepeating;
};

struct MouseMovedEvent
{
    Magnum::Vector2i position;
    Magnum::Vector2i relativePosition;
    Magnum::Platform::Sdl2Application::MouseMoveEvent::Buttons buttons;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
};

struct MousePressedEvent
{
    Magnum::Vector2i position;
    int clickCount;
    Magnum::Platform::Sdl2Application::MouseEvent::Button buttons;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
};

struct MouseReleasedEvent
{
    Magnum::Vector2i position;
    int clickCount;
    Magnum::Platform::Sdl2Application::MouseEvent::Button buttons;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
};

struct MoveEvent
{
    float x, y, z;
};

struct GameStarted {};

struct ShutDownEvent {};

struct ObjectDestroyed
{
    Entity object;
};
