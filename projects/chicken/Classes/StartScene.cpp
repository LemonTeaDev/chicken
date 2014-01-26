#include "StartScene.h"
#include "GameScene.h"
#include "Opening.h"
#include "CocosHelper.h"
#include "SoundManager.h"
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
    SoundManager::sharedSoundManager()->playTitleBgm();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //window size
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin(); // left down corner

	CCSprite* sprite = CCSprite::create("back-1.png");
	sprite->setPosition(ccp(visibleSize.width /2, visibleSize.height/2));
    sprite->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	this->addChild(sprite,0);

    CocosHelper::addSprite(this, "mainlogo.png", CCPointMake(visibleSize.width/2, visibleSize.height/2+50), 1,true,ccp(0.5f, 0.5f));
    
    CCSprite* handSpr = CocosHelper::addSprite(this, "main_hand.png", CCPointMake(30, visibleSize.height-50), 1,true,ccp(0.5f, 0.5f));
    handSpr->runAction(CCRepeatForever::create(CCSequence::create(CCMoveTo::create(10.0f,ccp(handSpr->getPosition().x+1000, handSpr->getPosition().y)),CCMoveTo::create(10.0f,ccp(100, handSpr->getPosition().y)),NULL)));
    
    CocosHelper::addSprite(this, "main_chicken.png", CCPointMake(visibleSize.width-215+50, 290/2-50), 1,true,ccp(0.5f, 0.5f));
    CCSprite* fogSpr = CocosHelper::addSprite(this, "front-ef.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 2,true,ccp(0.5f, 0.5f));
    fogSpr->setOpacity(0.85);
    
	CCMenuItemImage* pStart = CCMenuItemImage::create("main_startbt.png", "main_startbt.png", this, menu_selector(StartScene::menuStartCallback));
    pStart->setAnchorPoint(ccp(0.5, 0.5));
	pStart->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - pStart->getContentSize().height*2));

	CCMenu* pMenu = CCMenu::create(pStart, NULL);
	pMenu->setPosition(CCPointZero);
    //pMenu->setAnchorPoint(ccp(0.5f,0.5f));
	this->addChild(pMenu, 1);  
  
    return true;
}


void StartScene::menuStartCallback(CCObject* pSender)
{
    SoundManager::sharedSoundManager()->playButtonSound();
    ((CCNode*)(pSender))->runAction(CCSequence::create(CCScaleTo::create(0.25f, 1.1f),CCScaleTo::create(0.25f, 1.0f),CCCallFunc::create(this, callfunc_selector(StartScene::menuStartAniEnd)),NULL));
}

void StartScene::menuStartAniEnd(){
    //CCScene* pScene = OpeningOne::scene();
	CCScene* pScene = GameScene::scene();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
