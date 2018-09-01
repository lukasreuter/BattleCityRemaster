#pragma once

#include "Components.h"
#include <Magnum/Platform/Sdl2Application.h>
#include <entt.hpp>
#include <string>

typedef entt::DefaultRegistry::entity_type Entity;
typedef Magnum::Platform::Sdl2Application::KeyEvent KeyEvent;
typedef Magnum::Platform::Sdl2Application::MouseEvent MouseEvent;
typedef Magnum::Platform::Sdl2Application::MouseMoveEvent MouseMoveEvent;

struct HitEvent
{
    //HitEvent(std::string name, int points) : targetName{name}, points{points} {}
    
    std::string targetName;
    int points;
};

struct ShootEvent
{
    //ShootEvent(Entity entity, Position pos, Orientation bdir, Orientation tdir, std::string target) : entity{entity}, start{pos}, //bodyDirection{bdir}, turretDirection{tdir}, target{target} {}

    Position start;
    Orientation bodyDirection;
    Orientation turretDirection;
    Entity entity;
    std::string target;
};

struct KeyPressedEvent
{
    //KeyPressedEvent(const KeyEvent& event) : //} : event{event} {
    //ev{event.key(), event.modifiers(), event.isRepeated()} {
    //}
    
    Magnum::Platform::Sdl2Application::KeyEvent::Key key;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    bool isRepeating;
    
    //KeyEvent ev;
};

struct KeyReleasedEvent
{
    Magnum::Platform::Sdl2Application::KeyEvent::Key key;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    bool isRepeating;
    
    
    //KeyReleasedEvent(KeyEvent event) : event{event} {}

    //KeyEvent event;
};

struct MouseMovedEvent
{
    //MouseMovedEvent(MouseMoveEvent event) : event{event} {}
    
    //MouseMoveEvent event;
    
    //void free(){
        Magnum::Vector2i position;
        Magnum::Vector2i relativePosition;
        Magnum::Platform::Sdl2Application::MouseMoveEvent::Buttons buttons;
        Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
      //  MouseMoveEvent ev(position, relativePosition, buttons);
    //}
};

struct MousePressedEvent
{
    
    Magnum::Vector2i position;
    int clickCount;
    Magnum::Platform::Sdl2Application::MouseMoveEvent::Buttons buttons;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    
    //MousePressedEvent(MouseEvent event) : event{event} {}

    //MouseEvent event;
};

struct MouseReleasedEvent
{
    
    Magnum::Vector2i position;
    int clickCount;
    Magnum::Platform::Sdl2Application::MouseMoveEvent::Buttons buttons;
    Magnum::Platform::Sdl2Application::InputEvent::Modifiers modifiers;
    
    
    //MouseReleasedEvent(MouseEvent event) : event{event} {}

    //MouseEvent event;
};

struct MoveEvent
{
    //MoveEvent(int x, int y, int z) : x{x}, y{y}, z{z} {}
    
    int x, y, z;
};

struct GameStarted {};

struct ShutDownEvent {};

struct ObjectDestroyed
{
    //ObjectDestroyed(Entity obj) : object{obj} {}

    Entity object;
};
