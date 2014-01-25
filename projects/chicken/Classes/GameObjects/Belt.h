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
    void beltSpeedUp(float degree);
    void beltSpeedDown(float degree);
    void beltReverse();
private:
    CCSprite* beltSpr;
    CCAnimate *beltSprAnimate;
};
#endif