#include "Chicken.h"
#include "Food.h"
#include "CocosHelper.h"
#include "GameScene.h"
#include "Belt.h"
#include "ChickenField.h"
#include "SoundManager.h"
/////////////////////////////////////////////////
// init
/////////////////////////////////////////////////
/* virtual */
bool Chicken::init()
{
	// super init
	if (!CCNode::init())
	{
		return false;
	}
    InitializeLifeMax();
	InitializeLifeFatFactors();
	SetDigestSpeed(4);
	// Load Sprites
    for (int i = 0 ; i < max; i++) {
        if ((FatStatus)i == slim) {
            spriteFront[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_f_stand.png");
            spriteBack[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_b_stand.png");
        }
        if ((FatStatus)i == normal) {
            spriteFront[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_f_stand.png");
            spriteBack[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_b_stand.png");
        }
        if ((FatStatus)i == fat) {
            spriteFront[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_f_stand.png");
            spriteBack[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_b_stand.png");
        }
    }
    for (int i = 0 ; i < max; i++) {
        if ((FatStatus)i == slim) {
            spriteFront_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_f_eat.png");
            spriteBack_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_b_eat.png");
        }
        if ((FatStatus)i == normal) {
            spriteFront_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_f_eat.png");
            spriteBack_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_b_eat.png");
        }
        if ((FatStatus)i == fat) {
            spriteFront_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_f_eat.png");
            spriteBack_Eat[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_b_eat.png");
        }
    }
    for (int i = 0 ; i < max; i++) {
        if ((FatStatus)i == slim) {
            spriteFront_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_f_cry.png");
            spriteBack_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_slim_b_cry.png");
        }
        if ((FatStatus)i == normal) {
            spriteFront_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_f_cry.png");
            spriteBack_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_normal_b_cry.png");
        }
        if ((FatStatus)i == fat) {
            spriteFront_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_f_cry.png");
            spriteBack_Cry[(FatStatus)i] = CCTextureCache::sharedTextureCache()->addImage("nomal_chicken_fat_b_cry.png");
        }
    }
    
    
    chickenSpr = CocosHelper::addSprite(this, "nomal_chicken_normal_b_stand.png", CCPointMake(0,0), CHICKEN_SPR);
    chickenSpr->setTexture(spriteFront[normal]);
    chickenSpr->setAnchorPoint(ccp(.5f, .5f));
    
    
    CCMenuItem* menuItem = CCMenuItem::create(this, menu_selector(Chicken::chickenTouch));
    menuItem->setContentSize(chickenSpr->getContentSize());
    
	CCMenu* pMenu = CCMenu::createWithItem(menuItem);
    pMenu->setPosition(ccp(0, 0));
    pMenu->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(pMenu,CHICKEN_MENU,CHICKEN_MENU);
	
    
    healthSpr = CocosHelper::addSprite(this, "health_bar.png", CCPointMake(0,0), CHICKEN_HEALTHBAR, true, ccp(0.0f, 0.5f));
    healthSpr->setAnchorPoint(ccp(0.0f, 0.5f));
    //life = 25;
    UpdateHealthBar();

	scheduleUpdate();

	CCDelayTime* delayTime = CCDelayTime::create(GetDigestSpeed());
	CCCallFunc* funcCall = CCCallFunc::create(this, callfunc_selector(Chicken::Digest));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, funcCall, nullptr);
	this->runAction(seq);

	return true;
}

namespace
{
	static Belt* GetBelt(Chicken* pChicken)
	{
		GameScene* pGameScene =
			dynamic_cast<GameScene*>(
			CCDirector::sharedDirector()->getRunningScene()->getChildByTag(0));
		Belt* pBelt = nullptr;
		if (pGameScene != nullptr)
		{
			pBelt = dynamic_cast<Belt*>(
				pGameScene->getChildByTag(GAME_SCENE_BELT));
		}
		return pBelt;
	}
}

void Chicken::chickenTouch(CCObject* pSender){
    //CCLog("chickenTouch");
    CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
    Chicken* chicken =(Chicken*)menu->getParent();
    chicken->runAction(CCSequence::create(CCScaleTo::create(0.3f, 1.2f),CCScaleTo::create(0.3f, 1.0f),NULL));
    
	Belt* pBelt = GetBelt(this);
	Food* pFood = nullptr;
	if (pBelt != nullptr && (pFood = pBelt->findEatableFood(this)) != nullptr)
	{
		Eat(pFood);
	}
	else
	{
		SetChickenEvent(cry);
	}
}
/////////////////////////////////////////////////
// life : fatness factor initialize
/////////////////////////////////////////////////
/* virtual */ 
void Chicken::InitializeLifeFatFactors()
{
	lifeFatFactor[slim] = 0;
	lifeFatFactor[normal] = 30;
	lifeFatFactor[fat] = 70;
    
    digestRange = 3;
    digestValue = 5;
}

/////////////////////////////////////////////////
// Get Fat Status according to the life
/////////////////////////////////////////////////
Chicken::FatStatus Chicken::GetFatStatus() const
{
	if (life < lifeFatFactor[normal])
	{
		return slim;
	}
	else if (lifeFatFactor[normal] <= life &&
		life < lifeFatFactor[fat])
	{
		return normal;
	}
	else
	{
		return fat;
	}
}

bool Chicken::GetIsCaptureAble(){
    CCLog("GetIsCaptureAble life : %d",life);
	if (life <= 0)
	{
		return true;
	}

    if (lifeFatFactor[normal] > life ||
		life > lifeMax - (lifeMax-lifeFatFactor[fat]))
	{
		return true;
	}
    return false;
}
//////////////////////////////////////////////////////
// set max life (value differs by the chicken species)
//////////////////////////////////////////////////////
/* virtual */ void Chicken::InitializeLifeMax()
{
    life = 50;
	lifeMax = 100;
}

/////////////////////////////////////////////////
// General Update Logic per Tick
/////////////////////////////////////////////////
/* virtual */ void Chicken::update(float dt)
{
	CCNode::update(dt);
}

int Chicken::GetLife() const
{
	return life;
}

void Chicken::UpdateHealthBar(){
    if (life > lifeMax) {
        return ;
    }
    if (life <= lifeFatFactor[normal]) {
        healthSpr->setColor(ccc3(255,0,0));
    }else if (life <= lifeFatFactor[fat] ) {
        healthSpr->setColor(ccc3(0,255,0));
    }else{
        healthSpr->setColor(ccc3(255,255,0));
    }
    if (((float)life/(float)lifeMax) <= 0) {
        healthSpr->setScaleX(0);
    }else if(((float)life/(float)lifeMax) >= 1){
        healthSpr->setScaleX(1);
    }else{
        healthSpr->setScaleX(((float)life/(float)lifeMax));
    }
    SetFatStatus();
}
void Chicken::IncreaseLife(unsigned int delta)
{
	int _delta = static_cast<int>(delta);
	life += _delta;
	if (life > lifeMax)
	{
		life = lifeMax;
	}
	
    UpdateHealthBar();
}

void Chicken::DecreaseLife(unsigned int delta)
{
    CCLog("DecreaseLife : %d",delta);
    CCLog("DecreaseLife life: %d",life);

	int _delta = static_cast<int>(delta);
	life -= delta;
	if (life <= 0)
	{
		life = 1;
	}

    UpdateHealthBar();
}

void Chicken::SetLife(int life)
{
	this->life = life;
	if (life <= 0)
	{
		life = 1;
	}

	if (life > lifeMax)
	{
		life = lifeMax;
	}
	UpdateHealthBar();
}

/////////////////////////////////////////////////
// nom nom nom nom
/////////////////////////////////////////////////
void Chicken::Eat(Food* food)
{
	SetChickenEvent(eat);
	food->doEffect(this); // effect to chicken
	food->doEffect(GetBelt(this));	// effect to belt
	food->removeFromParentAndCleanup(true);
}

/////////////////////////////////////////////////
// Get Chicken's Looking side
/////////////////////////////////////////////////
Chicken::ChickenSide Chicken::GetChickenSide() const
{
	return side;
}

/////////////////////////////////////////////////
// Set Chicken's Looking side
/////////////////////////////////////////////////
void Chicken::SetChickenSide(ChickenSide chickenSide)
{
	side = chickenSide;
    
    if (chickenSide == front) {
        chickenSpr->setTexture(spriteFront[GetFatStatus()]);
        healthSpr->setPosition(CCPointMake(-90,chickenSpr->getContentSize().height/2-40));
    }else if(chickenSide == back){
        chickenSpr->setTexture(spriteBack[GetFatStatus()]);
        healthSpr->setPosition(CCPointMake(-90,-40));
    }
}

void Chicken::SetFatStatus(){
    if (side == front) {
        chickenSpr->setTexture(spriteFront[GetFatStatus()]);
    }else if(side == back) {
        chickenSpr->setTexture(spriteBack[GetFatStatus()]);
    }
    
}

void Chicken::SetChickenEvent(EventStatus chickenEvent)
{
	if (chickenEvent == eat) {
        CCAnimation* chickenSprAnimation = CCAnimation::create();
        chickenSprAnimation->setDelayPerUnit(0.3f);
        if (GetFatStatus() == slim) {
            if (side == front) {
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_f_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_f_stand.png");
            }else if (side == back){
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_b_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_b_stand.png");
            }
        }else if (GetFatStatus() == normal) {
            if (side == front) {
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_f_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_f_stand.png");
            }else if (side == back){
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_b_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_b_stand.png");
            }
        }else if (GetFatStatus() == fat) {
            if (side == front) {
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_f_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_f_stand.png");
            }else if (side == back){
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_b_eat.png");
                chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_b_stand.png");
            }
        }
        CCAnimate *animate = CCAnimate::create(chickenSprAnimation);
        chickenSpr->runAction(animate);
    }else if (chickenEvent == cry) {
        SoundManager::sharedSoundManager()->playEatFailSound();
        DecreaseLife(10);
        if (side == back) {
            return ;
        }
        CCAnimation* chickenSprAnimation = CCAnimation::create();
        chickenSprAnimation->setDelayPerUnit(0.3f);
        if (GetFatStatus() == slim) {
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_f_cry.png");
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_slim_f_stand.png");
        }else if (GetFatStatus() == normal) {
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_f_cry.png");
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_normal_f_stand.png");
        }else if (GetFatStatus() == fat) {
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_f_cry.png");
            chickenSprAnimation->addSpriteFrameWithFileName("nomal_chicken_fat_f_stand.png");
        }
        CCAnimate *animate = CCAnimate::create(chickenSprAnimation);
        chickenSpr->runAction(animate);
    }
}
/////////////////////////////////////////////////
// 닭의 소화 속도. 몇 초에 한번 포만감이 감소하나
/////////////////////////////////////////////////
unsigned int Chicken::GetDigestSpeed() const
{
	return digestSpeed;
}

void Chicken::SetDigestSpeed(unsigned int speed)
{
	digestSpeed = speed;
}


void Chicken::Digest()
{
    int range = (rand() % digestRange) - digestRange;
	DecreaseLife(digestValue+range);
    if (life > 0 && life < lifeMax) {
        CCDelayTime* delayTime = CCDelayTime::create(GetDigestSpeed());
        CCCallFunc* funcCall = CCCallFunc::create(this, callfunc_selector(Chicken::Digest));
        CCFiniteTimeAction* seq = CCSequence::create(delayTime, funcCall, nullptr);
        this->runAction(seq);
    }else{
        stopAllActions();
    }
}
void Chicken::SetIdx(unsigned int aIdx){
    idx = aIdx;
}
unsigned int Chicken::GetIdx() const{
    return idx;
}