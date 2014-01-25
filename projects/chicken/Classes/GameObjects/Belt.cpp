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
    beltSpr = CocosHelper::addSprite(this, "../Resources/belt-01.png", ccp(visibleSize.width/2, 220), 0, true, ccp(0.5f, 0.5f));
    
    
    runBeltAnimation(0.5f,false);
}

void Belt::runBeltAnimation(float speed, bool isReverse)
{
    CCAnimation* beltSprAnimation = CCAnimation::create();
    beltSprAnimation->setDelayPerUnit(speed);
    beltSprAnimation->addSpriteFrameWithFileName("../Resources/belt-02.png");
    beltSprAnimation->addSpriteFrameWithFileName("../Resources/belt-03.png");
    beltSprAnimation->addSpriteFrameWithFileName("../Resources/belt-04.png");
    beltSprAnimation->addSpriteFrameWithFileName("../Resources/belt-05.png");
    beltSprAnimation->addSpriteFrameWithFileName("../Resources/belt-06.png");
    
    CCAnimate *animate = CCAnimate::create(beltSprAnimation);
    CCRepeatForever *beltSprAnimate = CCRepeatForever::create(animate);
    beltSprAnimate->setTag(0);
    if (isReverse) {
        beltSpr->runAction(beltSprAnimate->reverse());
    }else{
        beltSpr->runAction(beltSprAnimate);
    }
}

void Belt::drawGear()
{

	//draw Gears
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	gear[0] = CCSprite::create("../Resources/gear3.png");
	gear[1] = CCSprite::create("../Resources/gear2.png");
	gear[2] = CCSprite::create("../Resources/gear1.png");

	gear[0]->setPosition(ccp(origin.x + (gear[0]->getContentSize().width) * 2, visibleSize.height / 2 - gear[0]->getContentSize().height + 2.0));
	gear[1]->setPosition(ccp(origin.x + gear[1]->getContentSize().width / 2 + 2.0, visibleSize.height / 2 - gear[0]->getContentSize().height - 13.0));
	gear[2]->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - gear[0]->getContentSize().height - gear[1]->getContentSize().height));

	for (int i = 0; i < 3; i++){

		this->addChild(gear[i], 2);
		gear[i]->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		CCRotateBy* rotateAction = CCRotateBy::create(5.0f, 60.0f);
		gear[i]->runAction(CCRepeatForever::create(rotateAction));
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