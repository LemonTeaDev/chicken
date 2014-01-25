#include "DietPill.h"
#include "Food.h"
#include "Belt.h"
#include "CocosHelper.h"
#include "Chicken.h"

DietPill* DietPill::create(int effectLevel)
{
	DietPill* pRet = new DietPill();
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

bool DietPill::init(int effectLevel)
{
	// super init
	if (!Food::init())
	{
		return false;
	}

	this->effectLevel = effectLevel;

	std::string spriteName;
	switch (effectLevel)
	{
	case 1:
		spriteName = "item_blue.png";
		break;
	case 2:
		spriteName = "item_yellow.png";
		break;
	case 3:
		spriteName = "item_red.png";
		break;
	case 4:
		spriteName = "item_50.png";
		break;
	}
	CCSprite* pSprite = CocosHelper::addSprite(this, spriteName.c_str(), CCPointMake(0, 0), 0);
	pSprite->setAnchorPoint(ccp(.5f, .5f));

	return true;
}

/* virtual */
void DietPill::doEffect(Chicken* pChicken) const
{
	if (pChicken != nullptr)
	{
		if (effectLevel <= 1)
		{
			pChicken->DecreaseLife(10);
		}
		else if (1 < effectLevel && effectLevel <= 2)
		{
			pChicken->DecreaseLife(30);
		}
		else if (2 < effectLevel && effectLevel <= 3)
		{
			pChicken->DecreaseLife(50);
		}
		else
		{
			pChicken->SetLife(50);
		}
	}
}

/* virtual */
void DietPill::doEffect(Belt* pBelt) const
{
	// dietpill is not effective for belt
}