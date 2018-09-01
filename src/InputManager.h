#pragma once

#include "Singleton.h"
#include "RenderManager.h"


class InputManager : public Singleton<InputManager>
{
public:
    InputManager();
    ~InputManager();
    void init();
    
    void setWindowExtents(int width, int height);
    
    inline bool keyPressed(const struct KeyPressedEvent& arg);
    inline bool keyReleased(const struct KeyReleasedEvent& arg);
//    inline bool mouseMoved(const OIS::MouseEvent &arg);
//    inline bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
//    inline bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id);
    
//    OIS::Mouse* getMouse();
//    OIS::Keyboard* getKeyboard();
/*
private:
    void capture();
    OIS::InputManager* mInputMgr;
    OIS::Mouse* mMouse;
    OIS::Keyboard* mKeyboard;
     */
};
