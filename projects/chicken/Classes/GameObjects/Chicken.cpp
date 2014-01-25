#include "Chicken.h"
#include "Food.h"
#include "CocosHelper.h"
#include "GameScene.h"
#include "Belt.h"

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
    //CCMenuItem* menuItem = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(Chicken::chickenTouch));
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
    CCLog("chickenTouch");

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
/* virtual */ void Chicken::InitializeLifeFatFactors()
{
	lifeFatFactor[slim] = 0;
	lifeFatFactor[normal] = 30;
	lifeFatFactor[fat] = 70;
}

/////////////////////////////////////////////////
// Get Fat Status according to the life
/////////////////////////////////////////////////
Chicken::FatStatus Chicken::GetFatStatus() const
{
#if 1
    return fat;
#endif
    
	if (lifeFatFactor[slim] <= life &&
		life < lifeFatFactor[normal])
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

unsigned int Chicken::GetLife() const
{
	return life;
}
void Chicken::UpdateHealthBar(){
    if (life <= 25) {
        healthSpr->setColor(ccc3(255,0,0));
    }else if (life <= 75) {
        healthSpr->setColor(ccc3(0,255,0));
    }else{
        healthSpr->setColor(ccc3(255,255,0));
    }
    healthSpr->setScaleX(((float)life/(float)lifeMax));
}
void Chicken::IncreaseLife(unsigned int delta)
{
	if (life + delta > lifeMax)
	{
		life = lifeMax;
	}
	else
	{
		life += delta;
	}
    UpdateHealthBar();
}

void Chicken::DecreaseLife(unsigned int delta)
{
	if (life - delta > 0)
	{
		life -= delta;
	}
	else
	{
		life = 0;
	}
    UpdateHealthBar();
}

void Chicken::SetLife(unsigned int life)
{
	this->life = max(min(lifeMax, life), 0);
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
	DecreaseLife(1);

	CCDelayTime* delayTime = CCDelayTime::create(GetDigestSpeed());
	CCCallFunc* funcCall = CCCallFunc::create(this, callfunc_selector(Chicken::Digest));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, funcCall, nullptr);
	this->runAction(seq);
}