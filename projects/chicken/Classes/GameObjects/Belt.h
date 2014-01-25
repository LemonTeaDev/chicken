#ifndef __chicken__Belt__
#define __chicken__Belt__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Belt : public CCNode
{
public:
    //Belt();
    virtual ~Belt();
    virtual bool init();
    void drawBackground();
    static Belt* create();
    void runBeltAnimation(float speed, bool isReverse);
    void beltSpeedUp(float degree);
    void beltSpeedDown(float degree);
    void beltReverse();

	void drawGear();
    
private:
    CCSprite* beltSpr;
	CCSprite* gear[3];//3개의 다른 기어
};
#endif