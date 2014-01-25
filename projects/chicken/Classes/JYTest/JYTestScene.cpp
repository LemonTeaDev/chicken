//
//  JYTestScene.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "JYTestScene.h"
#include "CocosHelper.h"
#include "SaveData.h"

USING_NS_CC;
JYTestScene::JYTestScene(){
    CCTextureCache::sharedTextureCache()->addImage("Icon-114.png");
    CCTextureCache::sharedTextureCache()->addImage("Icon-144.png");
    CCTextureCache::sharedTextureCache()->addImage("Icon-57.png");
}

JYTestScene::~JYTestScene(){
    
}
CCScene* JYTestScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    JYTestScene *layer = JYTestScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool JYTestScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    belt = Belt::create();
    belt->drawBackground();
    addChild(belt,0,0);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCMenuItemImage* pClose = CCMenuItemImage::create("../Resources/quit_test.png", "../Resources/quit_test.png", this, menu_selector(JYTestScene::menuCloseCallback));
	CCMenuItemImage* pStart = CCMenuItemImage::create("../Resources/start_test.png", "../Resources/start_test.png", this, menu_selector(JYTestScene::menuStartCallback));
    
    
	pClose->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	pStart->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - pClose->getContentSize().height));
    
	CCMenu* pMenu = CCMenu::create(pClose, pStart, NULL);
    pMenu->setAnchorPoint(ccp(0.5f,0.5f));
	pMenu->setPosition(CCPointMake(0, 0));
	addChild(pMenu, 1,1);
    

    return true;
}
void JYTestScene::menuCloseCallback(CCObject* pSender)
{
    belt->beltReverse();
}

void JYTestScene::menuStartCallback(CCObject* pSender)
{
    belt->beltSpeedUp(10.0f);
}