#pragma once

// Chicken Game
// Belt Speed Control
// ltearain, 2014. 01. 26

#include "cocos2d.h"
#include "Food.h"
USING_NS_CC;

class Chicken;
class Belt;
class Food;

class BeltSpeedCtrl : public Food
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(bool increase);
	static BeltSpeedCtrl* create(bool increase);

	virtual void doEffect(Chicken* pChicken) const override;
	virtual void doEffect(Belt* pBelt) const override;

private:
	bool increase;
};