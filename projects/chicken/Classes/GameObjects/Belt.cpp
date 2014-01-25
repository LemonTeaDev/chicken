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

	//왼쪽 기어
	gear[0] = CCSprite::create("../Resources/gear3.png");
	gear[1] = CCSprite::create("../Resources/gear2.png");
	gear[2] = CCSprite::create("../Resources/gear1.png");

	gear[0]->setPosition(ccp(origin.x + (gear[0]->getContentSize().width) * 2 + 4.0, 220 - 50.0));
	gear[1]->setPosition(ccp(origin.x + gear[1]->getContentSize().width / 2 + 4.0, 220 - 60.0));
	gear[2]->setPosition(ccp(origin.x + (gear[2]->getContentSize().width) * 3 - 4.5, 220 - 75.0));

	//오른쪽 기어
	gear[3] = CCSprite::create("../Resources/gear3.png");
	gear[4] = CCSprite::create("../Resources/gear2.png");
	gear[5] = CCSprite::create("../Resources/gear1.png");

	gear[3]->setPosition(ccp(visibleSize.width - (gear[0]->getContentSize().width) * 2 - 4.0, 220 - 50.0));
	gear[4]->setPosition(ccp(visibleSize.width - gear[1]->getContentSize().width / 2 - 4.0, 220 - 60.0));
	gear[5]->setPosition(ccp(visibleSize.width - (gear[2]->getContentSize().width) * 3 + 4.5, 220 - 75.0));




	for (int i = 0; i < 6; i++){

		this->addChild(gear[i], 2);
		gear[i]->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		CCRotateBy* rotateAction = CCRotateBy::create(3.0f, 60.0f);
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