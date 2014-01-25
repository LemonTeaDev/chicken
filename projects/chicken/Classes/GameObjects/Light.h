#ifndef __chicken__Light__
#define __chicken__Light__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class Light : public CCNode
{
public:
    virtual ~Light();
    virtual bool init();
    void drawBackground();
    static Light* create();
    
private:
    CCSprite* lightSpr;
};
#endif