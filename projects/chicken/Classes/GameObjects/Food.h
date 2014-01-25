#pragma  once

// Chicken Game
// Food
// ltearain, 2014. 01. 25

#include "cocos2d.h"
USING_NS_CC;

class Chicken;
class Belt;

class Food : public CCNode
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	CREATE_FUNC(Food)

	virtual void update(float dt) override;
	virtual void removeFromParentAndCleanup(bool cleanup) override;
	void _RemoveFromParentAndCleanup(bool cleanup);

	virtual void doEffect(Chicken* pChicken) const {}
	virtual void doEffect(Belt* pBelt) const {}
};