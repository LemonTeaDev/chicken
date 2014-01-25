// Chicken Game
// Food
// ltearain, 2014. 01. 25

#include "cocos2d.h"
USING_NS_CC;

class Food : public CCNode
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init() override;

	// implement the "static node()" method manually
	CREATE_FUNC(Food)

	virtual void update(float dt) override;
	virtual void removeFromParentAndCleanup(bool cleanup) override;
private:

};