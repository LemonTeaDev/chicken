#ifndef __chicken__Master__
#define __chicken__Master__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Master : public CCNode
{
public:
    virtual ~Master();
    virtual bool init();
    void drawBackground();
    static Master* create();
    void runStartAction(CCPoint point, bool isUp);
    void runGrapAction();
private:
    CCSprite* masterSpr;
    bool isUp;
};
#endif