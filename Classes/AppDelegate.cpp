#include "AppDelegate.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "lua_tinker.h"
#include "Net.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "AdmobHelper.h"

void showAds()
{
	AdmobHelper::showAds();
}
#endif

using namespace CocosDenshion;

USING_NS_CC;

extern int luaopen_net(lua_State* tolua_S);
extern int luaopen_update(lua_State* tolua_S);

void registerLuas(lua_State* tolua_S)
{
	luaopen_net(tolua_S);
}

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
	auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLView::create("OpenBird");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		glview->setFrameSize(450.f, 800.f);
#endif
        director->setOpenGLView(glview);
    }

	director->setNotificationNode(Net::getInstance());

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	auto screenSize = glview->getFrameSize();

    auto designSize = Size(288.f, 512.f);

    auto fileUtils = FileUtils::getInstance();

	fileUtils->addSearchPath("./Resources");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    // a bug in DirectX 11 level9-x on the device prevents ResolutionPolicy::NO_BORDER from working correctly
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
#else
	glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
#endif

    // register lua engine
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    registerLuas(engine->getLuaStack()->getLuaState());
    //The call was commented because it will lead to ZeroBrane Studio can't find correct context when debugging
    engine->executeString("require 'main.lua'");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//AdmobHelper::showAds();
	//bind func to lua
	lua_State * L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
	lua_tinker::def(L, "showAds", showAds);
#endif
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
