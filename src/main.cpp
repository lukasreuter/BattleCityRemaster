#include <Magnum/GL/DefaultFramebuffer.h>
#include <Magnum/Platform/Sdl2Application.h>

#include <Magnum/GL/Context.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Version.h>
#include <Magnum/Math/Color.h>
#include <Magnum/Timeline.h>

#include <entt.hpp>

//#include "Battlecity.h"
#include "DotSceneLoader.h"
#include "Factory.h"
#include "MovementManager.h"
#include "PlayerManager.h"
#include "MapManager.h"
#include "AIManager.h"
#include "CollisionManager.h"
#include "MessageManager.h"
#include "HeatingManager.h"
#include "HealthManager.h"
#include "ShootManager.h"
#include "ScoreManager.h"
#include "ParticleManager.h"
#include "SoundManager.h"
#include "InputManager.h"

#include "Logger.h"

using namespace Magnum;
using namespace Magnum::Math::Literals;

class BattleCityApp: public Platform::Application {
public:
	explicit BattleCityApp(const Arguments& arguments);

    void receive([[maybe_unused]] const ShutDownEvent &event) { _quitGame = true; }
private:
	void drawEvent() override;
	void tickEvent() override;
	
	bool _quitGame = false;
	Timeline _timeline;
    entt::DefaultRegistry registry;
};

BattleCityApp::BattleCityApp(const Arguments& arguments): Platform::Application{arguments, NoCreate}
{
	{
        /// create the actual window config. we can set the window title that way
		const Vector2 dpiScaling = this->dpiScaling({});
		Configuration conf;
		conf.setTitle("BattleCity 2018")
			.setSize(conf.size(), dpiScaling);
		GLConfiguration glConf;

		if (!tryCreate(conf, glConf))
			create(conf, glConf);
	}

	GL::Renderer::setClearColor(0xa5c9ea_rgbf);
	
	LOGD("Hello! BattleCity2018 is running on"
		<< GL::Context::current().version() << "using"
		<< GL::Context::current().rendererString())
	
	_quitGame = false;
	RenderManager::GetRef().init("Battlecity");
	LOGD("RENDER configured")
	auto & SoundManager = SoundManager::GetRef();
	//SoundManager.init();
	//SoundManager.loadFiles();
	//LOGD("Sound configured")
	InputManager::GetRef().init();
	LOGD("INPUT configured")
	//ScreenManager::GetRef().init(MenuScreen::GetRef());
	LOGD("SCREEN configured")
	
    //RenderManager::GetRef().setFrameListener(this);
	//LOGD("FRAME LISTENER attached")
	PlayerManager::GetRef().init();
	LOGD("PLAYER configured")
	MapManager::GetRef().init();
	LOGD("MAP configured")
	MovementManager::GetRef().init();
	LOGD("MOVEMENT configured")
	AIManager::GetRef().init();
	LOGD("AI configured")
	HealthManager::GetRef().init();
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

void BattleCityApp::drawEvent() {
	GL::defaultFramebuffer.clear(GL::FramebufferClear::Color);

	/* TODO: Add your drawing code here */
	
	/// get the delta time elapsed since the last frame
	auto dt = _timeline.previousFrameDuration();
	
	//if(RenderManager::getPtr()->getRenderWindow()->isClosed())
	  //  return false;
	
	/// after all systems have been updated, actually draw to the screen
	//RenderManager::getPtr()->update(dt);
	//return !quitGame;

	swapBuffers();
	_timeline.nextFrame();
}

void BattleCityApp::tickEvent()
{
    auto dt = _timeline.previousFrameDuration();
    
	//InputManager::GetRef().update();
	
	//ScreenManager::getPtr()->update(dt);
	
	//AIManager::getPtr()->update(dt);
	
    HeatingManager::GetRef().Update(dt, registry);
	
	//MovementManager::getPtr()->update(dt);
	
	//ParticleManager::getPtr()->update(dt);
	
	//RenderManager::getPtr()->update(dt);
}

MAGNUM_APPLICATION_MAIN(BattleCityApp)
