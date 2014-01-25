#include "Belt.h"
#include "CocosHelper.h"


Belt::~Belt(){
    
}

Belt *Belt::create()
{
    Belt *pRet = new Belt();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}
bool Belt::init()
{
    if ( !CCNode::init() )
    {
        return false;
    }
    
    this->setContentSize(CCDirector::sharedDirector()->getVisibleSize());
    for (int i = 1; i < 7 ;i++) {
        char filename[0X20];
        sprintf(filename, "belt-%02d",i);
        CCTextureCache::sharedTextureCache()->addImage(filename);
    }
    drawBackground();
    return true;
}

 
void Belt::drawBackground(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    beltSpr = CocosHelper::addSprite(this, "belt-01.png", ccp(visibleSize.width/2, 220), 0, true, ccp(0.5f, 0.5f));
    
    
    runBeltAnimation(0.5f,false);
}

void Belt::runBeltAnimation(float speed, bool isReverse)
{
    CCAnimation* beltSprAnimation = CCAnimation::create();
    beltSprAnimation->setDelayPerUnit(speed);
    beltSprAnimation->addSpriteFrameWithFileName("belt-02.png");
    beltSprAnimation->addSpriteFrameWithFileName("belt-03.png");
    beltSprAnimation->addSpriteFrameWithFileName("belt-04.png");
    beltSprAnimation->addSpriteFrameWithFileName("belt-05.png");
    beltSprAnimation->addSpriteFrameWithFileName("belt-06.png");
    
    CCAnimate *animate = CCAnimate::create(beltSprAnimation);
    CCRepeatForever *beltSprAnimate = CCRepeatForever::create(animate);
    beltSprAnimate->setTag(0);
    if (isReverse) {
        beltSpr->runAction(beltSprAnimate->reverse());
    }else{
        beltSpr->runAction(beltSprAnimate);
    }
}


void Belt::beltSpeedUp(float degree){
    beltSpr->stopAllActions();
    runBeltAnimation(0.3f,false);
}
void Belt::beltSpeedDown(float degree){
   beltSpr->stopAllActions();
    runBeltAnimation(0.7f,false);
}
void Belt::beltReverse(){
    beltSpr->stopAllActions();
    runBeltAnimation(0.5f,true);
}