#include "BeltSpeedCtrl.h"
#include "Food.h"
#include "Belt.h"
#include "CocosHelper.h"
#include "Chicken.h"
#include "SoundManager.h"
BeltSpeedCtrl* BeltSpeedCtrl::create(bool increase)
{
	BeltSpeedCtrl* pRet = new BeltSpeedCtrl();
	if (pRet && pRet->init(increase))
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

bool BeltSpeedCtrl::init(bool increase)
{
	// super init
	if (!Food::init())
	{
		return false;
	}

	std::string spriteName;
	if (increase)
	{
		spriteName = "item_up.png";
	}
	else
	{
		spriteName = "item_down.png";
	}

	CCSprite* pSprite = CocosHelper::addSprite(this, spriteName.c_str(), CCPointMake(0, 0), 0);
	pSprite->setAnchorPoint(ccp(.5f, .5f));

	return true;
}

/* virtual */
void BeltSpeedCtrl::doEffect(Chicken* pChicken) const
{
	// beltSpeedCtrl is not effective for chicken
}

/* virtual */
void BeltSpeedCtrl::doEffect(Belt* pBelt) const
{
	if (pBelt != nullptr)
	{
		if (increase)
		{
			pBelt->beltSpeedUp(10);
		}
		else
		{
			pBelt->beltSpeedDown(10);
		}
	}
    SoundManager::sharedSoundManager()->playItemSound();
}