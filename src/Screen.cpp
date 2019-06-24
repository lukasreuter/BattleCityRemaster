#include "Screen.h"
#include "RenderManager.h"
#include "InputManager.h"
#include "ScreenManager.h"
#include "Messages.h"
#include "MapManager.h"
#include "PlayerManager.h"
#include "Factory.h"
#include "ScreenManager.h"
#include "EntityManager.h"
#include "Components.h"
#include "ScoreManager.h"
#include "Logger.h"
#include <iostream>

/****** SCREEN BASE CLASS ******/


/****** MENU SCREEN******/
void MenuScreen::Enter()
{/*
    mTrayMgr = new SdkTrayManager("MenuTray",RenderManager::getPtr()->getRenderWindow(),
                                  InputManager::getPtr()->getMouse(), this);
    mEntities = entityx::EntityManager::make(MessageManager::getPtr()->getEventMgr());

    //Ogre::Overlay *bclogo = Ogre::OverlayManager::getSingletonPtr()->getByName("BattlecityLogo");

    mTrayMgr->createDecorWidget(TL_TOP, "BCLOGO", "BattlecityLogo");

    mTrayMgr->createButton(TL_CENTER, "NewGameButton", "Nuova Partita", 200);
    mTrayMgr->createButton(TL_CENTER, "ExitButton", "Esci", 200);
    change = false;

    MessageManager::getPtr()->emit<GameStarted>();
  */
}

void MenuScreen::Pause()
{
    //mTrayMgr->hideAll();
}

void MenuScreen::Resume()
{
    //mTrayMgr->showAll();
}

void MenuScreen::Leave()
{/*
    mTrayMgr->destroyAllWidgets();
    delete mTrayMgr;
    mTrayMgr = 0;
  */
}
/*
void MenuScreen::buttonHit(Button *button)
{
    std::string buttonName = button->getName();

    if(buttonName == "ExitButton"){
        mTrayMgr->showYesNoDialog("Quit the Game?","Do you want to quit?");
    }

    if(buttonName == "NewGameButton"){
        change = true;
    }

}*/

void MenuScreen::Update(float)
{
    if (change) {
        ScreenManager::GetRef().ChangeScreen<PlayScreen>();
    }
}

void MenuScreen::YesNoDialogClosed(const std::string& question, bool yesHit)
{
    if (yesHit && question == "Do you want to quit?") {
        MessageManager::GetRef().emit<ShutDownEvent>();
    }
}

/****** PlayScreen ******/
void PlayScreen::Enter()
{/*
    mEntities = entityx::EntityManager::make(MessageManager::getPtr()->getEventMgr());

    mTrayMgr = new SdkTrayManager("PlayTray",RenderManager::getPtr()->getRenderWindow(),
                                  InputManager::getPtr()->getMouse(), this);

    // DRAW GUI
    Ogre::StringVector infoPanelStr;
    unsigned int screenWidth = RenderManager::getPtr()->getRenderWindow()->getWidth();
    infoPanelStr.push_back("Score");
    mInfoPanel = mTrayMgr->createParamsPanel(TL_TOP, "InfoPanel", screenWidth * .20, infoPanelStr);
    mHealthBar = mTrayMgr->createProgressBar(TL_BOTTOMLEFT, "HealthBar","Health", screenWidth * .25, 50);
    mHeatBar = mTrayMgr->createProgressBar(TL_BOTTOMRIGHT, "HeatBar", "Heat", screenWidth * .25, 50);
    mHealthBar->setComment(" ");
    mHeatBar->setComment(" ");

    mInfoPanel->setParamValue("Score",Ogre::StringConverter::toString(0));
    mHealthBar->setProgress(1);
    mHeatBar->setProgress(1);

    mTrayMgr->hideCursor();


    Ogre::Light* luce;

    luce = RenderManager::getPtr()->getSceneManager()->createLight();
    luce->setType(Ogre::Light::LT_POINT);
    luce->setPowerScale(2.0);
    luce->setPosition(-125, 10, -125);

    luce = RenderManager::getPtr()->getSceneManager()->createLight();
    luce->setType(Ogre::Light::LT_POINT);
    luce->setPowerScale(2.0);
    luce->setPosition(125, 10, -125);

    luce = RenderManager::getPtr()->getSceneManager()->createLight();
    luce->setType(Ogre::Light::LT_POINT);
    luce->setPowerScale(2.0);
    luce->setPosition(-125, 10, 125);

    luce = RenderManager::getPtr()->getSceneManager()->createLight();
    luce->setType(Ogre::Light::LT_POINT);
    luce->setPowerScale(2.0);
    luce->setPosition(125, 10, 125);

    RenderManager::getPtr()->getSceneManager()->setAmbientLight(Ogre::ColourValue::White);




    Entity tank1 = Factory::createTank(mEntities, "Player", 45, 65, Ogre::Vector3(100, 20, 100), 1000, false);

    tank1.assign<Position>(MapManager::getPtr()->getFreePos());
    tank1.assign<Destroyable>(1000);

    PlayerManager::getPtr()->setPlayerEntity(tank1);

    entityx::Entity tankcpu0;

    for (int i = 0; i < 5; ++i) {
        char prefix[15];
        sprintf(prefix,"CPU%d",i);
        tankcpu0 = Factory::createTank(mEntities, prefix,30,60,Ogre::Vector3(100,60,100),500, true);
        tankcpu0.assign<Position>(MapManager::getPtr()->getFreePos());
    }

    entityx::ptr<Children> children = tank1.component<Children>();
    entityx::ptr<Renderable> cameraParent = children->children["turret"].component<Renderable>();
    RenderManager::getPtr()->attachCameraTo(cameraParent->sceneNode, Ogre::Vector3(0,4.5,20));

    //RenderManager::getPtr()->getSceneManager()->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    Factory::createFloor(mEntities, 250, 250, 20, 20, "Floor");
    MapManager::getPtr()->print_maze(mEntities);
*/
}

void PlayScreen::Pause()
{
  //  mTrayMgr->hideAll();
}

void PlayScreen::Resume()
{
    //mTrayMgr->showAll();
    //mTrayMgr->hideCursor();
}

void PlayScreen::Leave()
{/*
    mEntities->destroy_all();
    RenderManager::getPtr()->getSceneManager()->getRootSceneNode()->removeAndDestroyAllChildren();
    RenderManager::getPtr()->getSceneManager()->destroyAllLights();
    mTrayMgr->destroyAllWidgets();
    delete mTrayMgr;
    mTrayMgr = 0;
  */
}

void PlayScreen::Update(float)
{
    Entity player = PlayerManager::GetPlayer();
    auto& registry = EntityManager::Registry();
    
    if (registry.valid(player))
    {
        auto& dest = registry.get<Destroyable>(player);
        auto& heat = registry.get<OverHeating>(player);
        double healthPercent = static_cast<double>(dest.health) / dest.maxHealth;
        double heatPercent = 1 - (static_cast<double>(heat.overheating) / heat.maxheating);
       /* mHealthBar->setComment(Ogre::StringConverter::toString(dest->health));
        mHeatBar->setComment(Ogre::StringConverter::toString((int) (heatPercent * 100)));
        mHealthBar->setProgress(healthPercent);
        mHeatBar->setProgress(heatPercent);*/
    }/*
    mInfoPanel->setParamValue("Score",
                              Ogre::StringConverter::toString(ScoreManager::getPtr()->getScore()));*/
}

void PlayScreen::mouseMoved(const MouseMovedEvent& evt)
{
    Screen::mouseMoved(evt);
    PlayerManager::GetRef().handleMouseMoved(evt);
}

void PlayScreen::mousePressed(const MousePressedEvent& evt)
{
    Screen::mousePressed(evt);
    PlayerManager::GetRef().handleMousePressed(evt);
}

void PlayScreen::mouseReleased(const MouseReleasedEvent& evt)
{
    Screen::mouseReleased(evt);
    PlayerManager::GetRef().handleMouseReleased(evt);
}

void PlayScreen::keyPressed(const KeyPressedEvent& evt)
{
    PlayerManager::GetRef().handleKeyPressed(evt);
}
 
void PlayScreen::keyReleased(const KeyReleasedEvent& evt)
{
    using Key = Magnum::Platform::Sdl2Application::KeyEvent::Key;
    
    if (evt.key == Key::Esc) {
        ScreenManager::GetRef().PushScreen<PauseScreen>();
    } else {
        PlayerManager::GetRef().handleKeyReleased(evt);
    }
}


/**** PauseScreen *****/

void PauseScreen::Enter()
{/*
    mEntities = entityx::EntityManager::make(MessageManager::getPtr()->getEventMgr());

    mTrayMgr = new SdkTrayManager("PauseTray",RenderManager::getPtr()->getRenderWindow(),
                                  InputManager::getPtr()->getMouse(), this);

    Ogre::Real buttonWidth = RenderManager::getPtr()->getRenderWindow()->getWidth() *.25;
    mTrayMgr->createButton(TL_CENTER, "ResumeGameButton","Resume Game", buttonWidth);
    mTrayMgr->createButton(TL_CENTER, "ReturnButton", "Return to Main Menu", buttonWidth);
    mTrayMgr->createButton(TL_CENTER, "QuitButton", "Quit Game", buttonWidth);
  */
}

void PauseScreen::Pause()
{
    //mTrayMgr->hideAll();
}

void PauseScreen::Resume()
{
    //mTrayMgr->showAll();
}

void PauseScreen::Leave()
{/*
    mTrayMgr->destroyAllWidgets();
    delete mTrayMgr;
    mTrayMgr = 0;*/
}
/*
void PauseScreen::buttonHit(Button *button)
{
    std::string buttonName = button->getName();
    if(buttonName == "ResumeGameButton")
        ScreenManager::getPtr()->popScreen();
    if(buttonName == "ReturnButton")
        ScreenManager::getPtr()->resetTo(MenuScreen::getPtr());
    if(buttonName == "QuitButton")
        mTrayMgr->showYesNoDialog("Quit the Game?","Do you want to quit?");

}*/

void PauseScreen::YesNoDialogClosed(const std::string& question, bool yesHit)
{
    if (yesHit && question == "Do you want to quit?") {
        MessageManager::GetRef().emit<ShutDownEvent>();
    }
}

void PauseScreen::keyReleased(const KeyReleasedEvent& evt)
{
    using Key = Magnum::Platform::Sdl2Application::KeyEvent::Key;
    
    if (evt.key == Key::Esc) {
        ScreenManager::GetRef().PopScreen();
    }
}

/**** GameOverScreen *****/

void GameOverScreen::Enter()
{/*
    mEntities = entityx::EntityManager::make(MessageManager::getPtr()->getEventMgr());

    mTime = screenDuration;

    Ogre::RenderWindow *window = RenderManager::getPtr()->getRenderWindow();
    float width = window->getWidth() * .25;

    mTrayMgr = new SdkTrayManager("GameOverTray",window, InputManager::getPtr()->getMouse(), this);

    mTrayMgr->createLabel(TL_CENTER,"GameOverNotice", "Game Over", width);
    mTrayMgr->createLabel(TL_CENTER,"GameOverScore", "Your Score: " +
                          Ogre::StringConverter::toString(ScoreManager::getPtr()->getScore()) ,
                          width);
*/
}

void GameOverScreen::Pause()
{
    //mTrayMgr->hideAll();
}

void GameOverScreen::Resume()
{
    //mTrayMgr->showAll();
}

void GameOverScreen::Leave()
{/*
    mTrayMgr->destroyAllWidgets();
    delete mTrayMgr;
    mTrayMgr = 0;
*/
}

void GameOverScreen::Update(float dt)
{
    _time -= dt;

    LOGD("Tempo rimasto: " << _time);

    if (_time <= 0) {
        _time = screenDuration;
        ScoreManager::GetRef().ResetScore();
        ScreenManager::GetRef().ChangeScreen<MenuScreen>();
    }
}
