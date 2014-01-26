#include "StartScene.h"
#include "GameScene.h"
#include "Opening.h"
USING_NS_CC;

CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{

	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //window size
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin(); // left down corner

	CCSprite* sprite = CCSprite::create("main_page.png");
	sprite->setPosition(ccp(visibleSize.width /2, visibleSize.height/2));
    sprite->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	this->addChild(sprite,0);

	CCMenuItemImage* pStart = CCMenuItemImage::create("main_startbt.png", "main_startbt.png", this, menu_selector(StartScene::menuStartCallback));

	pStart->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - pStart->getContentSize().height*2));

	CCMenu* pMenu = CCMenu::create(pStart, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);  
  
    return true;
}


void StartScene::menuStartCallback(CCObject* pSender)
{
	CCScene* pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
