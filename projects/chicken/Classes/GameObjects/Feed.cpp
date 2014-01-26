#include "Feed.h"
#include "Food.h"
#include "Belt.h"
#include "CocosHelper.h"
#include "Chicken.h"
#include "SoundManager.h"
Feed* Feed::create(int effectLevel)
{
	Feed* pRet = new Feed();
	if (pRet && pRet->init(effectLevel))
	{ 
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return pRet;
	}
}

bool Feed::init(int effectLevel)
{
	// super init
	if (!Food::init())
	{
		return false;
	}

	this->effectLevel = effectLevel;

	std::string spriteName = std::string("item_feed") + std::to_string(effectLevel) + std::string(".png");
	CCSprite* pSprite = CocosHelper::addSprite(this, spriteName.c_str(), CCPointMake(0, 0), 0);
	pSprite->setAnchorPoint(ccp(.5f, .5f));

	return true;
}

/* virtual */
void Feed::doEffect(Chicken* pChicken) const
{
	if (pChicken != nullptr)
	{
		if (effectLevel <= 1)
		{
			pChicken->IncreaseLife(20);
		}
		else if (1 < effectLevel && effectLevel <= 2)
		{
			pChicken->IncreaseLife(40);
		}
		else
		{
			pChicken->IncreaseLife(60);
		}
	}
    SoundManager::sharedSoundManager()->playEatSound();
}

/* virtual */
void Feed::doEffect(Belt* pBelt) const
{
	// feed is not effective for belt
}