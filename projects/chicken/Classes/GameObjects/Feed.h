#pragma once

// Chicken Game
// Feed
// ltearain, 2014. 01. 25

#include "cocos2d.h"
#include "Food.h"
USING_NS_CC;

class Chicken;
class Belt;
class Food;

class Feed : public Food
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(int effectLevel);
	static Feed* create(int effectLevel);

	virtual void doEffect(Chicken* pChicken) const override;
	virtual void doEffect(Belt* pBelt) const override;

private:
	int effectLevel;
};