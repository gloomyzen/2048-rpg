#include <battleModule/battleCore.h>
#include "AppDelegate.h"
#include "common/coreModule/gameManager.h"
#include "common/coreModule/enums/statesEnums.h"
#include "common/coreModule/scenes/scenesFactory/scenesFactoryInstance.h"
#include "common/coreModule/resources/settings/settingManager.h"
#include "metaModule/metaTabs.h"

// #define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {}

AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
	AudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs() {
	// set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
	GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

	GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages() {
	return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto setting = common::coreModule::settingManager::load();
	// initialize director
	auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("Mercenary Battles", cocos2d::Rect(0, 0, setting.largeResolutionSize.width, setting.largeResolutionSize.height));
#else
		glview = GLViewImpl::create("Mercenary Battles");
#endif
		director->setOpenGLView(glview);
	}

	// turn on display FPS
	director->setDisplayStats(setting.showDisplayStats);

	// set FPS. the default value is 1.0/60 if you don't call this
	director->setAnimationInterval(1.0f / 60);

	// Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
	director->setContentScaleFactor(1);
#else
	glview->setDesignResolutionSize(setting.frameResolutionSize.width, setting.frameResolutionSize.height, ResolutionPolicy::FIXED_HEIGHT);
#endif

	register_all_packages();
	GET_SCENES_FACTORY().registerState(common::coreModule::eGameStates::BATTLE_SCENE, [](Layer* node)->Layer*{
		auto _background = cocos2d::Sprite::create("images/ui/windows/testWindow/background.png");
		_background->setName("background");
		_background->setAnchorPoint(Vec2(0.f, 0.f));
		node->addChild(_background);
		auto battle = new sr::battleModule::battleCore();
		node->addChild(battle);

		return node;
	});

	GET_SCENES_FACTORY().registerState(common::coreModule::eGameStates::MAIN_MENU, [](Layer* node)->Layer*{
		auto _background = cocos2d::Sprite::create("images/ui/windows/testWindow/background.png");
		_background->setName("background");
		_background->setAnchorPoint(Vec2(0.f, 0.f));
		node->addChild(_background);
		auto meta = new sr::metaModule::metaTabs();
		node->addChild(meta);

		return node;
	});

	GET_GAME_MANAGER().run(common::coreModule::eGameStates::BATTLE_SCENE);

	return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
	Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::pauseAll();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
	AudioEngine::resumeAll();
#endif
}
