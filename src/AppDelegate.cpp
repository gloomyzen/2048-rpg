#include "common/coreModule/resources/resourceManager.h"
#include "AppDelegate.h"
#include "common/coreModule/gameManager.h"
#include "common/coreModule/scenes/scenesFactory/scenesFactoryInstance.h"
#include "common/coreModule/resources/settings/settingManager.h"
//all profile block header
#include "common/profileModule/profileManager.h"
//all databases header
#include "common/databaseModule/databaseInterface.h"
#include "common/databaseModule/databaseManager.h"
//widgets
#include "interfaceModule/customNodeTypes.h"
//all scenes
//todo

#define USE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#endif

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
#if USE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->end();
#endif
    GET_PROFILE().cleanup();
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
    auto setting = GET_RESOLUTION_SETTING();
    setting->load();
    cocos2d::FileUtils::getInstance()->setPopupNotify(false);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    setting->init(false, "frameResolution");
#else
    setting->init(true);
#endif
    auto currentResolution = setting->getCurrentSize();
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    if (!glView) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glView = GLViewImpl::createWithRect("Swipe RPG", cocos2d::Rect(0, 0, currentResolution->size.width, currentResolution->size.height), currentResolution->scale);
#else
        glView = GLViewImpl::create("Swipe RPG");
#endif
        director->setOpenGLView(glView);
    }

    // turn on display FPS
    director->setDisplayStats(currentResolution->showStats);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // set project view mode
    director->setProjection(Director::Projection::_2D);
    cocos2d::Sprite::setUsePixelMode(currentResolution->spritePixel);

    // Set the design resolution
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
    director->setContentScaleFactor(1.f);
//	glView->setFrameZoomFactor(1.f);
	glView->setResolutionPolicy(ResolutionPolicy::EXACT_FIT);
#else
    glView->setDesignResolutionSize(currentResolution->size.width, currentResolution->size.height, ResolutionPolicy::EXACT_FIT);
#endif

    register_all_packages();
    // register all profile
    //todo add profile blocks
//    GET_PROFILE().registerBlock("local", [](){ return new sr::localProfile::localProfileBlock(); });
    GET_PROFILE().executeLoad();
    // register all databases
    //todo add databases
//    GET_DATABASE_MANAGER().registerDatabase({"coursesDb", "properties/database/library/db.json"}, new sr::databasesModule::coursesDatabase());
    GET_DATABASE_MANAGER().executeLoadData();
    //register external node types
    sr::interfaceModule::customNodeTypes::registerAllCustomNodes();
    // register all states
    GET_SCENES_FACTORY().registerState("metaScene", [](Layer* node)->Layer*{
//           auto scene = new sr::metaScene::metaScene();
//           node->addChild(scene);
           return node;
    });

    //run first scene
    GET_GAME_MANAGER().run("metaScene");

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
#endif
}
