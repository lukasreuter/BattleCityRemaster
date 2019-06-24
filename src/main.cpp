/**
 @file      main.cpp
 @author    Lukas Reuter
 @date      26.08.18

Copyright (c) 2018 till 2019, Lukas Reuter
All rights reserved.

*/

#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <Magnum/GL/Context.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Timeline.h>

#include <entt.hpp>

//#include "Battlecity.h"
#include "Factory.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "MapManager.h"
#include "AIManager.h"
#include "MessageManager.h"
#include "HeatingManager.h"
#include "HealthManager.h"
#include "ShootManager.h"
#include "ScoreManager.h"
#include "ParticleManager.h"
#include "SoundManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "DebugManager.h"

#include "Logger.h"

using namespace Magnum;
using namespace Magnum::Math::Literals;

class BattleCityApp: public Platform::Application
{
public:
	explicit BattleCityApp(const Arguments& arguments);

    void receive(const ShutDownEvent&) { _quitGame = true; }

private:
	void drawEvent() override;
	void tickEvent() override;

	void viewportEvent(Sdl2Application::ViewportEvent& event) override;

	void keyPressEvent(KeyEvent& event) override;

	void keyReleaseEvent(KeyEvent& event) override;

	bool _quitGame = false;
	Timeline _timeline;
};

BattleCityApp::BattleCityApp(const Arguments& arguments) : Platform::Application{ arguments,
    Configuration{}.setTitle("BattleCity 2018").setWindowFlags(Configuration::WindowFlag::Resizable) }
{
//    {
//        /// create the actual window config. we can set the window title that way
//        const Vector2 dpiScaling = this->dpiScaling({});
//        Configuration conf;
//        conf.setTitle("BattleCity 2018")
//            .setSize(conf.size(), dpiScaling);
//        GLConfiguration glConf;
//
//        if (!tryCreate(conf, glConf))
//            create(conf, glConf);
//    }

	GL::Renderer::setClearColor(0xa5c9ea_rgbf);
    setSwapInterval(1);
    setMinimalLoopPeriod(16);

	LOGD("Hello! BattleCity2018 is running on"
		<< GL::Context::current().version() << "using"
		<< GL::Context::current().rendererString())

//    _quitGame = false;

    /// MessageManager need to be the first component to init, everyone else depends on it
    auto& m = MessageManager::GetRef();
    /// not init the entity manager, other need it for preparing their components
    auto& e = EntityManager::GetRef();
    auto& registry = e.GetRegistry();

    auto& d = DebugManager::GetRef();

	RenderManager::GetRef().init("Battlecity");
	LOGD("RENDER configured")
	auto & SoundManager = SoundManager::GetRef();
	//SoundManager.init();
	//SoundManager.loadFiles();
	//LOGD("Sound configured")
	auto& InputManager = InputManager::GetRef();
    ScreenManager::GetRef().Init<MenuScreen>();
	LOGD("SCREEN configured")

    //RenderManager::GetRef().setFrameListener(this);
	//LOGD("FRAME LISTENER attached")
	PlayerManager::GetRef().init();
	LOGD("PLAYER configured")
	MapManager::GetRef().Init();
	LOGD("MAP configured")
	MovementManager::GetRef().Init(registry);
	LOGD("MOVEMENT configured")
	AIManager::GetRef().Init(registry);
	LOGD("AI configured")
	auto& h = HealthManager::GetRef();
	LOGD("HEALTH configured")
	ShootManager::GetRef().init();
	LOGD("SHOOT configured")
	ScoreManager::GetRef().Init();
	LOGD("SCORE configured")
	ParticleManager::GetRef().init();
	LOGD("PARTICLE configured")
	MessageManager::GetRef().subscribe<ShutDownEvent>(this);


	/// actually start the frame and dt counting for the update functions
	_timeline.start();
}

void BattleCityApp::drawEvent()
{
    /// this is the render update, will only be called when the draw has been requested by dirtying the state with redraw()

	GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);


	/// get the delta time elapsed since the last frame
	auto dt = _timeline.previousFrameDuration();

	//if(RenderManager::getPtr()->getRenderWindow()->isClosed())
	  //  return false;

	/// after all systems have been updated, actually draw to the screen
//    RenderManager::GetRef()->update(dt);

    /// swap front with the back buffer
	swapBuffers();
    /// advance the frame and time counter
	_timeline.nextFrame();
    // temp
    redraw();
}

void BattleCityApp::tickEvent()
{
    /// this is the place where the simulation is run
    bool dirtyRender = false;

    auto dt = _timeline.previousFrameDuration();

    auto& registry = EntityManager::GetRef().GetRegistry();

	//ScreenManager::getPtr()->update(dt);

    AIManager::GetRef().Update(dt, registry);

    HeatingManager::GetRef().Update(dt, registry);

	MovementManager::GetRef().Update(dt, registry);

	//ParticleManager::getPtr()->update(dt);

	//RenderManager::getPtr()->update(dt);

    dirtyRender |= true;
    if (dirtyRender) {
//        redraw();
    }
}

void BattleCityApp::viewportEvent(Platform::Sdl2Application::ViewportEvent& event)
{

}

void BattleCityApp::keyPressEvent(KeyEvent& event)
{
	InputManager::GetRef().keyPressed(event);
    event.setAccepted();
}

void BattleCityApp::keyReleaseEvent(KeyEvent& event)
{
	InputManager::GetRef().keyReleased(event);
    event.setAccepted();
}

MAGNUM_APPLICATION_MAIN(BattleCityApp)
