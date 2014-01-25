#ifndef __chicken__Belt__
#define __chicken__Belt__

#include "cocos2d.h"
#include <deque>
USING_NS_CC;

using namespace std;
class Food;
class Chicken;

class Belt : public CCNode
{
public:
	const static float MIN_SPEED;
	const static float DEFAULT_SPEED;
	const static float MAX_SPEED;
	inline float SpeedToTimeTick(float speed) const;

public:
    virtual ~Belt();
	virtual bool init() override;
    void drawBackground();
    static Belt* create();
    void runBelt();
    void beltSpeedUp(float degree);
    void beltSpeedDown(float degree);
	void beltPause(float time);
    void beltReverse();
	bool GetIsReverse() const { return isReverse; }

	Food* findEatableFood(CCPoint chickenLocation);
	void loadFood(Food* pFood);
	void unloadFood(Food* pFood, bool cleanup = true);
    
	void drawGear();
    
private:
    CCSprite* beltSpr;
    int beltIdx;

	deque<Food*> foodList;

	float beltSpeed;
	bool isReverse;
	CCSprite* gear[6];//3개의 다른 기어
};
#endif