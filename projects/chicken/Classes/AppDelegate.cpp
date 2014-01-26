#include "AppDelegate.h"
#include "StartScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "Opening.h"

#include "SoundManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object


   // CCScene *pGameScene = GameScene::scene();
	//CCScene *pScene = GameOverScene::scene();
	CCScene *pGameScene = OpeningOne::scene();
	//CCScene *pGameScene = GameOverScene::scene();


    // run
//    CCDirector::sharedDirector()->setDepthTest(true);
	CCScene* transition = CCTransitionCrossFade::create(1.5f, pGameScene);
    
    pDirector->runWithScene(transition);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    SoundManager::sharedSoundManager()->getAudioEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
	SoundManager::sharedSoundManager()->getAudioEngine()->resumeBackgroundMusic();
}
