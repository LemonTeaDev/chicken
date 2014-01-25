#include "Belt.h"
#include "Utility/CocosHelper.h"
#include "Chicken.h"
#include "Food.h"
#include <algorithm>
#include "CocosHelper.h"

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
	scheduleUpdate();

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
    beltSpr = CocosHelper::addSprite(this, "../Resources/belt-01.png", ccp(visibleSize.width/2, 220), 0, true, ccp(0.5f, 0.5f));
    
    runBelt();
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




	for (int i = 0; i < 6; i++)
	{
		this->addChild(gear[i], 2);
		gear[i]->setAnchorPoint(CCPointMake(0.5f, 0.5f));
		CCRotateBy* rotateAction = CCRotateBy::create(3.0f, 60.0f);
		gear[i]->runAction(CCRepeatForever::create(rotateAction));
	}

}
void Belt::beltSpeedUp(float degree)
{
	if (degree < 0)
	{
		assert(!"invalid degree-");
		return;
	}

	beltSpeed = min(MAX_SPEED, beltSpeed + degree);

    beltSpr->stopAllActions();
	runBelt();
}

void Belt::beltSpeedDown(float degree)
{
	if (degree < 0)
	{
		assert(!"invalid degree-");
		return;
	}

	beltSpeed = max(MIN_SPEED, beltSpeed - degree);

   beltSpr->stopAllActions();
	runBelt();
}

void Belt::beltPause(float time)
{
	beltSpr->stopAllActions();
	scheduleOnce(schedule_selector(Belt::runBelt), 1.0f);
}

void Belt::beltReverse()
{
    beltSpr->stopAllActions();
	isReverse = !isReverse;
	runBelt();
}

Food* Belt::findEatableFood(CCPoint chickenLocation)
{
	auto itrFood = std::find_if(
		foodList.begin(),
		foodList.end(),
		[](Food* food) -> bool {
		if (food == nullptr)
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
				auto chickenLeftTop = CocosHelper::getLeftTopPos(food);
				auto chickenRightBottom = CocosHelper::getRightBottomPos(food);
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
		// TODO 음식을 벨트에 올린다 (addchild)
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
			pFood->removeFromParentAndCleanup(cleanup);
			pFood = nullptr;
		}
	}
}