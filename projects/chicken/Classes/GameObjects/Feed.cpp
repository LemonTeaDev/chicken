#include "Feed.h"
#include "Food.h"
#include "Belt.h"
#include "CocosHelper.h"
#include "Chicken.h"

/* virtual */
bool Feed::init()
{
	// super init
	if (!Food::init())
	{
		return false;
	}

	CCSprite* pSprite = CocosHelper::addSprite(this, "item_feed1.png", CCPointMake(0, 0), 0);
	pSprite->setAnchorPoint(ccp(.5f, .5f));

	return true;
}

/* virtual */
void Feed::doEffect(Chicken* pChicken) const
{

}

/* virtual */
void Feed::doEffect(Belt* pBelt) const
{

}