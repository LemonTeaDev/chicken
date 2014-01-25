#include "Master.h"
#include "CocosHelper.h"
#include "SoundManager.h"
#include "ChickenField.h"
Master::~Master(){
    
}

Master *Master::create()
{
    Master *pRet = new Master();
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
bool Master::init()
{
    if ( !CCNode::init() )
    {
        return false;
    }
    
    this->setContentSize(CCDirector::sharedDirector()->getVisibleSize());
    this->setAnchorPoint(ccp(0.5f, 0.5f));
    for (int i = 1; i < 2 ;i++) {
        char filename[0x20];
        sprintf(filename, "hand_%02d.png",i);
        CCTextureCache::sharedTextureCache()->addImage(filename);
    }
    drawBackground();
    return true;
}


void Master::drawBackground(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    masterSpr = CocosHelper::addSprite(this, "hand_01.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 0);
    masterSpr->setAnchorPoint(CCPointMake(0.5f, 0.5f));
}

void Master::runStartAction(CCPoint point, bool aIsUp, ChickenField* aRemoveChickenField,int idx){
    SoundManager::sharedSoundManager()->playHandSound();
    isUp = aIsUp;
    removeChickenField = aRemoveChickenField;
    removeIdx = idx;
    CCPoint adjustPoint = point;
    if (isUp) {
        setRotation(180);
        adjustPoint.y = adjustPoint.y+55;
    }else{
        adjustPoint.y = adjustPoint.y-55;
    }
    CCSequence* sequence = CCSequence::create(CCMoveTo::create(0.2f, adjustPoint),CCCallFunc::create(this, callfunc_selector(Master::runGrapAction)) ,NULL);
    runAction(sequence);
}

void Master::runGrapAction(){    
    CCAnimation* masterSprAnimation = CCAnimation::create();
    masterSprAnimation->setDelayPerUnit(0.3f);
    masterSprAnimation->addSpriteFrameWithFileName("hand_02.png");
    
    CCAnimate *masterSprAnimate = CCAnimate::create(masterSprAnimation);
    CCSequence* sequence = CCSequence::create(masterSprAnimate,CCRemoveSelf::create(),NULL);
    masterSpr->runAction(sequence);
    
    removeChickenField->RemoveChicken(removeIdx);
    runAction(CCSequence::create(CCDelayTime::create(2.0f),CCCallFunc::create(this, callfunc_selector(Master::reSpawn)),NULL));
}

void Master::reSpawn(){
    Chicken* chicken = Chicken::create();
    if (removeIdx <= 4) {
        chicken->SetChickenSide(Chicken::front);
    }else{
        chicken->SetChickenSide(Chicken::back);
    }
    chicken->setScale(0.0f);
    chicken->SetIdx(removeIdx-1);
    removeChickenField->AddChicken(removeIdx, chicken);
    chicken->runAction(CCScaleTo::create(0.5f, 1.0f));
}