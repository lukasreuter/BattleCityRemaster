#include "InputManager.h"
#include "MessageManager.h"
#include "Logger.h"


InputManager::InputManager()
{
    LOGD(GREENBOLD << "InputManger" << RESET << "configured")
}

void InputManager::keyPressed(const KeyEvent &arg)
{
    MessageManager::GetRef().emit<KeyPressedEvent>(arg.key(), arg.modifiers(), arg.isRepeated());
}

void InputManager::keyReleased(const KeyEvent& arg)
{
    MessageManager::GetRef().emit<KeyReleasedEvent>(arg.key(), arg.modifiers(), arg.isRepeated());
}

void InputManager::mouseMoved(MouseMoveEvent& arg)
{
    MessageManager::GetRef().emit<MouseMovedEvent>(arg.position(), arg.relativePosition(), arg.buttons(), arg.modifiers());
}

void InputManager::mousePressed(MouseEvent& arg)
{
    MessageManager::GetRef().emit<MousePressedEvent>(arg.position(), arg.clickCount(), arg.button(), arg.modifiers());
}

void InputManager::mouseReleased(MouseEvent& arg)
{
    MessageManager::GetRef().emit<MouseReleasedEvent>(arg.position(), arg.clickCount(), arg.button(), arg.modifiers());
}
