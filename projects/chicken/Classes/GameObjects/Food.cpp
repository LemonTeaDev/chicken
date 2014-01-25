#include "Food.h"
#include "Belt.h"

/* virtual */
bool Food::init()
{
	// super init
	if (!CCNode::init())
	{
		return false;
	}

	scheduleUpdate();
	return true;
}

/* virtual */
void Food::removeFromParentAndCleanup(bool cleanup)
{
	auto parent = dynamic_cast<Belt*>(getParent());
	if (parent != nullptr)
	{
		parent->unloadFood(this, cleanup);
	}
}

/* virtual */
void Food::update(float dt)
{
	Belt* belt = dynamic_cast<Belt*>(getParent());
	if (belt != nullptr)
	{
		if (!belt->getIsReverse())
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

			// right direction (left to right)
			// only check out of right boundary
			if (getPositionX() > visibleSize.width)
			{
				removeFromParentAndCleanup(true);
			}
		}
		else
		{
			// reverse direction (right to left)
			// only check out of left boundary
			if (getPositionX() < 0)
			{
				removeFromParentAndCleanup(true);
			}
		}
	}
}