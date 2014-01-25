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
    addChild(belt,0);
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCMenuItem* pUp = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(JYTestScene::menuCloseCallback));
	pUp->setTag(1);
    CCMenuItem* pDown = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(JYTestScene::menuCloseCallback));
    pDown->setTag(2);
    CCMenuItem* pReverse = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(JYTestScene::menuCloseCallback));
    pReverse->setTag(3);
    
	pUp->setPosition(ccp(50, origin.y + visibleSize.height / 2));
	pDown->setPosition(ccp(50, origin.y + visibleSize.height / 2 - pUp->getContentSize().height-30));
    pReverse->setPosition(ccp(50, origin.y + visibleSize.height / 2 - pUp->getContentSize().height-150));
    CCArray* menuItemArr = CCArray::create(pUp,pDown,pReverse,NULL);
	CCMenu* pMenu = CCMenu::createWithArray(menuItemArr);

    pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
    
    CCLog("this : %p",this);
    return true;
}
void JYTestScene::menuCloseCallback(CCObject* pSender)
{
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    
	int tag = (int)pMenuItem->getTag();
    CCLog("TAG : %d",tag);
    if (tag == 1) {
        CCMenu* menu = (CCMenu*)pMenuItem->getParent();
        JYTestScene* scene = (JYTestScene*)menu->getParent();
        scene->belt->beltSpeedUp(10.0f);
    }else if (tag == 2){
        CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
        JYTestScene* scene = (JYTestScene*)menu->getParent();
        scene->belt->beltSpeedDown(10.0f);
    }else if(tag == 3){
        CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
        JYTestScene* scene = (JYTestScene*)menu->getParent();
        scene->belt->beltReverse();
    }
}

void JYTestScene::menuStartCallback(CCObject* pSender)
{
    CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
    JYTestScene* scene = (JYTestScene*)menu->getParent();
    scene->belt->beltSpeedUp(10.0f);
}
void JYTestScene::menuReverseCallback(CCObject* pSender)
{
    CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
    JYTestScene* scene = (JYTestScene*)menu->getParent();
    scene->belt->beltReverse();
}