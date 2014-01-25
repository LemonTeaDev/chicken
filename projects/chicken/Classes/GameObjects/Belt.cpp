#include "Belt.h"
#include "Utility/CocosHelper.h"

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
    return true;
}

 
void Belt::drawBackground(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    beltSpr = CocosHelper::addSprite(this, "belt-01.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 0);
    beltSpr->setAnchorPoint(CCPointMake(0.5f, 0.5f));
    CCAnimation* anim = CCAnimation::create();
    anim->setDelayPerUnit(0.3f);
    anim->addSpriteFrameWithFileName("belt-02.png");
    anim->addSpriteFrameWithFileName("belt-03.png");
    anim->addSpriteFrameWithFileName("belt-04.png");
    anim->addSpriteFrameWithFileName("belt-05.png");
    anim->addSpriteFrameWithFileName("belt-06.png");
    
    beltSprAnimate = CCAnimate::create(anim);
    beltSpr->runAction(CCRepeatForever::create(beltSprAnimate));
}

void Belt::beltSpeedUp(float degree){
    float value = beltSprAnimate->getAnimation()->getDelayPerUnit();
    beltSprAnimate->getAnimation()->setDelayPerUnit(value*0.8f);
}
void Belt::beltSpeedDown(float degree){
    
}
void Belt::beltReverse(){
    beltSpr->runAction(CCRepeatForever::create(beltSprAnimate->reverse()));
}