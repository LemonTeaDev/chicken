#include "GameOverScene.h"
#include "GameScene.h"
#include "StartScene.h"
//#include "layers_scenes_transitions_nodes\CCTransitionPageTurn.h"
#include "CCDirector.h"

USING_NS_CC;

CCScene* GameOverScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameOverScene *layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}

	

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCMenuItemImage *pReplay = CCMenuItemImage::create("../Resources/replay.png", "../Resources/replay.png", this, menu_selector(GameOverScene::menuStartCallback));
	CCMenuItemImage *pQuit = CCMenuItemImage::create("../Resources/quit.png", "../Resources/quit.png", this, menu_selector(GameOverScene::menuCloseCallback));

	pReplay->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	pQuit->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - pQuit->getContentSize().height));

	CCMenu* pMenu = CCMenu::create(pReplay, pQuit, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	/*
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		this,
		menu_selector(GameOverScene::menuCloseCallback));

	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width / 2,
		origin.y + pCloseItem->getContentSize().height / 2));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	CCLabelTTF* pLabel = CCLabelTTF::create("Game Over!", "Arial", 24);

	// position the label on the center of the screen
	pLabel->setPosition(ccp(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - pLabel->getContentSize().height));

	// add the label as a child to this layer
	this->addChild(pLabel, 1);

	// add "GameOverScene" splash screen"
	CCSprite* pSprite = CCSprite::create("../Resources/HelloWorld.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width / 2 + origin.x, visibleSize.height));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	CCSprite* replay = CCSprite::create("../Resources/HelloWorld.png");
	*/

	return true;
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
#else
	CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
#endif
}

void GameOverScene::menuStartCallback(CCObject* pSender)
{
	CCScene *pScene = GameScene::scene();
	CCDirector::sharedDirector()->pushScene(pScene);
}