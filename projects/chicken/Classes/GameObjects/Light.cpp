#include "Light.h"
#include "Utility/CocosHelper.h"


Light::~Light(){
    
}

Light *Light::create()
{
    Light *pRet = new Light();
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
bool Light::init()
{
    if ( !CCNode::init() )
    {
        return false;
    }
    
    this->setContentSize(CCDirector::sharedDirector()->getVisibleSize());
    this->setAnchorPoint(ccp(0.5f, 0.5f));
    for (int i = 1; i < 4 ;i++) {
        char filename[0X20];
        sprintf(filename, "light-%d",i);
        CCTextureCache::sharedTextureCache()->addImage(filename);
    }
    drawBackground();
    return true;
}


void Light::drawBackground(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    lightSpr = CocosHelper::addSprite(this, "light-1.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 0);
    lightSpr->setAnchorPoint(CCPointMake(0.5f, 0.5f));
    CCAnimation* lightSprAnimation = CCAnimation::create();
    lightSprAnimation->setDelayPerUnit(0.3f);
    lightSprAnimation->addSpriteFrameWithFileName("light-2.png");
    lightSprAnimation->addSpriteFrameWithFileName("light-3.png");
    
    CCAnimate *animate = CCAnimate::create(lightSprAnimation);
    CCRepeatForever *lightSprAnimate = CCRepeatForever::create(animate);
    lightSprAnimate->setTag(0);
    lightSpr->runAction(lightSprAnimate);
}