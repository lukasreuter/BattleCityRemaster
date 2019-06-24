#pragma once

#include "Screen.h"
#include "Singleton.h"
#include "MessageManager.h"
#include <entt.hpp>
#include <vector>


class ScreenManager : public Singleton<ScreenManager>
{
    // holds all the screens in a stack-like fashion
    std::vector<std::unique_ptr<Screen>> _screens;
    
public:
    ScreenManager() = default;
    ~ScreenManager();

    template<typename T>
    void Init()
    {
        auto& dispatcher = MessageManager::GetRef().GetDispatcher();
        dispatcher.sink<KeyPressedEvent>().connect<&ScreenManager::ReceiveKeyPressedEvent>(this);
        dispatcher.sink<KeyReleasedEvent>().connect<&ScreenManager::ReceiveKeyReleasedEvent>(this);
        dispatcher.sink<MouseMovedEvent>().connect<&ScreenManager::ReceiveMouseMovedEvent>(this);
        dispatcher.sink<MousePressedEvent>().connect<&ScreenManager::ReceiveMousePressedEvent>(this);
        dispatcher.sink<MouseReleasedEvent>().connect<&ScreenManager::ReceiveMouseReleasedEvent>(this);
        //!@todo
        //Ogre::FontManager::getSingleton().getByName("SdkTrays/Caption")->load();
        PushScreen<T>();
    };


    template<typename T>
    void PushScreen()
    {
        if (not _screens.empty()) {
            _screens.back()->Pause();
        }

        _screens.emplace_back(std::make_unique<T>())->Enter();
        //_screens.back()->Enter();
    }

    void PopScreen();

    template<typename T>
    void ChangeScreen()
    {
        PopScreen();
        PushScreen<T>();
    }

    template<typename T>
    void ResetTo()
    {
        while (not _screens.empty()) {
            _screens.back()->Leave();
            _screens.pop_back();
        }

        PushScreen<T>();
    }

    void Update(float dt);

    //bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    void ReceiveKeyPressedEvent(const KeyPressedEvent& event);
    void ReceiveKeyReleasedEvent(const KeyReleasedEvent& event);
    void ReceiveMouseMovedEvent(const MouseMovedEvent& event);
    void ReceiveMousePressedEvent(const MousePressedEvent& event);
    void ReceiveMouseReleasedEvent(const MouseReleasedEvent& event);
};
