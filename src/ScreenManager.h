#pragma once

#include "Screen.h"
#include "Singleton.h"
#include <entt.hpp>
#include <vector>


class ScreenManager : public Singleton<ScreenManager>
{
public:
    ScreenManager() = default;
    ~ScreenManager();

    void Init(Screen *initialScreen);


    template <typename T>
    void PushScreen()
    {
        if (!_screens.empty())
            _screens.back()->Pause();

        _screens.push_back(std::make_unique<T>());
        _screens.back()->Enter();
    }

    void PopScreen();

    template <typename T>
    void ChangeScreen()
    {
        PopScreen();
        PushScreen<T>();
    }

    template <typename T>
    void ResetTo()
    {
        while (!_screens.empty()) {
            _screens.back()->Leave();
            _screens.pop_back();
        }

        PushScreen<T>();
    }

    void Update(float dt);

    //bool frameRenderingQueued(const Ogre::FrameEvent &evt);

    void receive(const struct KeyPressedEvent& event);
    void receive(const struct KeyReleasedEvent& event);
    void receive(const struct MouseMovedEvent& event);
    void receive(const struct MousePressedEvent& event);
    void receive(const struct MouseReleasedEvent& event);

private:
    std::vector<std::unique_ptr<Screen>> _screens;
};
