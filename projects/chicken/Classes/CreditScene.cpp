//
//  CreditScene.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 26..
//
//

#include "CreditScene.h"
#include "CocosHelper.h"

USING_NS_CC;
CreditScene::CreditScene(){
    
}

CreditScene::~CreditScene(){
    
}
CCScene* CreditScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CreditScene *layer = CreditScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CreditScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    
    CCSprite* spr = CocosHelper::addSprite(this, "credit_in.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 0, true, ccp(0.5f,0.5f));
    return true;
}
bool CreditScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCDirector::sharedDirector()->popScene();
    return true;
}
