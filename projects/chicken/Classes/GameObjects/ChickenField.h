// Chicken Game
// Chicken Field
// ltearain, 2014. 01. 25

#include "cocos2d.h"
USING_NS_CC;

class ChickenField : public CCLayer
{
public:
	static const int layerCount = 8;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(ChickenField)

public:
	

private:

};