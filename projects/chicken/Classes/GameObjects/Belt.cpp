#include "Belt.h"
#include "CocosHelper.h"
#include "Chicken.h"
#include "Food.h"
#include "Feed.h"
#include "DietPill.h"
#include "BeltSpeedCtrl.h"
#include <algorithm>
#include "CocosHelper.h"
#include <random>
#include "SoundManager.h"
const float Belt::MIN_SPEED = 0.01f;
const float Belt::MAX_SPEED = 100.0f;
const float Belt::DEFAULT_SPEED = 2.0f;

/* virtual */
Belt::~Belt()
{
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

	beltSpeed = DEFAULT_SPEED;
	isReverse = false;

    drawBackground();
	drawGear();
	runBelt();
	generateFoods();

    return true;
}

float Belt::SpeedToTimeTick(float speed) const
{
	if (speed > 0)
	{
		return 1 / speed;
	}
	else
	{
		return 1 / MIN_SPEED;
	}
}
 
void Belt::drawBackground(){
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    beltSpr = CocosHelper::addSprite(this, "belt-01.png", ccp(visibleSize.width/2, 220), 0, true, ccp(0.5f, 0.5f));
}

void Belt::runBelt()
{
    CCAnimation* beltSprAnimation = CCAnimation::create();
    beltSprAnimation->setDelayPerUnit(SpeedToTimeTick(beltSpeed));

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

	// move food
	// chicken width hard coded..
	int reverse = isReverse? -1 : 1;
	CCMoveBy* foodMover = CCMoveBy::create(SpeedToTimeTick(beltSpeed), CCPointMake(reverse * 250, 0));
	CCRepeatForever* foodMoverRepeated = CCRepeatForever::create(foodMover);
	for (auto food = foodList.begin(); food != foodList.end(); ++food)
	{
		if (*food != nullptr)
		{
			(*food)->stopAllActions();
			(*food)->runAction(foodMoverRepeated);
		}
	}

	// run gear
	for (int i = 0; i < 6; i++)
	{
		CCRotateBy* rotateAction = CCRotateBy::create(3.0f, 60.0f);
		gear[i]->runAction(CCRepeatForever::create(rotateAction));
	}
}

void Belt::drawGear()
{
	//draw Gears
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	// left gear
	gear[0] = CCSprite::create("gear3.png");
	gear[1] = CCSprite::create("gear2.png");
	gear[2] = CCSprite::create("gear1.png");

	gear[0]->setPosition(ccp(origin.x + (gear[0]->getContentSize().width) * 2 + 4.0, 220 - 50.0));
	gear[1]->setPosition(ccp(origin.x + gear[1]->getContentSize().width / 2 + 4.0, 220 - 60.0));
	gear[2]->setPosition(ccp(origin.x + (gear[2]->getContentSize().width) * 3 - 4.5, 220 - 75.0));

	// right gear
	gear[3] = CCSprite::create("gear3.png");
	gear[4] = CCSprite::create("gear2.png");
	gear[5] = CCSprite::create("gear1.png");

	gear[3]->setPosition(ccp(visibleSize.width - (gear[0]->getContentSize().width) * 2 - 4.0, 220 - 50.0));
	gear[4]->setPosition(ccp(visibleSize.width - gear[1]->getContentSize().width / 2 - 4.0, 220 - 60.0));
	gear[5]->setPosition(ccp(visibleSize.width - (gear[2]->getContentSize().width) * 3 + 4.5, 220 - 75.0));

	for (int i = 0; i < 6; i++)
	{
		this->addChild(gear[i], 3);
		gear[i]->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	}
}

void Belt::beltSpeedUp(float degree)
{
	if (degree < 0)
	{
		assert(!"invalid degree-");
		return;
	}

	beltSpeed = min(MAX_SPEED, beltSpeed*0.9f);

    beltSpr->stopActionByTag(0);
	runBelt();
    SoundManager::sharedSoundManager()->beltSoundPitch *= 0.9;
}

void Belt::beltSpeedDown(float degree)
{
	if (degree < 0)
	{
		assert(!"invalid degree-");
		return;
	}

	beltSpeed = max(MIN_SPEED, beltSpeed*1.1f);

	beltSpr->stopActionByTag(0);
	runBelt();
    SoundManager::sharedSoundManager()->beltSoundPitch *= 1.1;
}

void Belt::beltPause(float time)
{
	beltSpr->stopAllActions();

	// stop gears
	for (int i = 0; i < 6; i++)
	{
		gear[i]->stopAllActions();
	}

	CCDelayTime* delayTime = CCDelayTime::create(time);
	CCCallFunc* funcCall = CCCallFunc::create(this, callfunc_selector(Belt::runBelt));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, funcCall, nullptr);
	this->runAction(seq);
}

void Belt::beltReverse()
{
    beltSpr->stopAllActions();
	isReverse = !isReverse;
	runBelt();
}

Food* Belt::findEatableFood(Chicken* pChicken)
{
	auto itrFood = std::find_if(
		foodList.begin(),
		foodList.end(),
		[pChicken](Food* food) -> bool {
		if (food == nullptr || pChicken == nullptr)
		{
			return false;
		}
		else
		{
			std::pair<float, float> xBoundaryFood;
			{
				auto foodLeftTop = CocosHelper::getLeftTopPos(food);
				auto foodRightBottom = CocosHelper::getRightBottomPos(food);
				xBoundaryFood = make_pair(foodLeftTop.x, foodRightBottom.x);
			}

			std::pair<float, float> xBoundaryChicken;
			{
				if (pChicken->getParent() == nullptr)
				{
					return false;
				}
				auto chickenLeftTop = CocosHelper::getLeftTopPos(pChicken->getParent());
				auto chickenRightBottom = CocosHelper::getRightBottomPos(pChicken->getParent());
				xBoundaryChicken = make_pair(chickenLeftTop.x, chickenRightBottom.x);
			}

			return (xBoundaryChicken.first <= xBoundaryFood.first) &&
				(xBoundaryFood.second <= xBoundaryChicken.second);
		}
	});

	if (itrFood == foodList.end())
	{
		return nullptr;
	}
	else
	{
		return *itrFood;
	}
}

void Belt::loadFood(Food* pFood)
{
	if (pFood != nullptr)
	{
		foodList.push_back(pFood);

		if (getIsReverse())
		{
			pFood->setPosition(CCPointMake(1400, 293));
		}
		else
		{
			pFood->setPosition(CCPointMake(-100, 293));
		}
        
        //pFood->setPosition(ccp(1400, 293));
		addChild(pFood);
		int reverse = isReverse ? -1 : 1;
		CCMoveBy* foodMover = CCMoveBy::create(SpeedToTimeTick(beltSpeed), CCPointMake(reverse * 250, 0));
		CCRepeatForever* foodMoverRepeated = CCRepeatForever::create(foodMover);
		pFood->runAction(foodMoverRepeated);
	}
}

void Belt::unloadFood(Food* pFood, bool cleanup /* = true */)
{
	if (pFood != nullptr)
	{
		auto itrFood = std::find(foodList.begin(), foodList.end(), pFood);
		if (itrFood != foodList.end())
		{
			foodList.erase(itrFood);
			pFood->_RemoveFromParentAndCleanup(cleanup);
			pFood = nullptr;
		}
	}
}

void Belt::generateFoods()
{
	static uniform_int_distribution<int> dist(0, 100);

	int randomNumber = dist(randomEngine);
	if (0 <= randomNumber && randomNumber < 40)
	{
		// LV1 모이 (40%)
		Food* pFood = Feed::create(1);
		loadFood(pFood);
	}
	else if (40 <= randomNumber && randomNumber < 70)
	{
		// Lv2 모이 (30%)
		Food* pFood = Feed::create(2);
		loadFood(pFood);
	}
	else if (70 <= randomNumber && randomNumber < 80)
	{
		// LV3 모이 (10%)
		Food* pFood = Feed::create(3);
		loadFood(pFood);
	}
	else if (80 <= randomNumber && randomNumber < 90)
	{
		// LV1 다이어트약 (10%)
		Food* pFood = DietPill::create(1);
		loadFood(pFood);
	}
	else if (90 <= randomNumber && randomNumber < 93)
	{
		Food* pFood = DietPill::create(2);
		loadFood(pFood);
	}
	else if (93 <= randomNumber && randomNumber < 95)
	{
		Food* pFood = DietPill::create(3);
		loadFood(pFood);
	}
	else if (95 <= randomNumber && randomNumber < 96)
	{
		// 밸런스약
		Food* pFood = DietPill::create(4);
		loadFood(pFood);
	}
	else if (96 <= randomNumber && randomNumber < 98)
	{
		// 벨트속도 증가
		Food* pFood = BeltSpeedCtrl::create(true);
		loadFood(pFood);
	}
	else
	{
		// 벨트속도 감소
		Food* pFood = BeltSpeedCtrl::create(false);
		loadFood(pFood);
	}

	CCDelayTime* delayTime = CCDelayTime::create(SpeedToTimeTick(beltSpeed) * 5);
	CCCallFunc* funcCall = CCCallFunc::create(this, callfunc_selector(Belt::generateFoods));
	CCFiniteTimeAction* seq = CCSequence::create(delayTime, funcCall, nullptr);
	this->runAction(seq);
}
