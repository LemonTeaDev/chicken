#ifndef __chicken__Master__
#define __chicken__Master__

#include "cocos2d.h"
class ChickenField;
USING_NS_CC;
using namespace std;

class Master : public CCNode
{
public:
    virtual ~Master();
    virtual bool init();
    void drawBackground();
    static Master* create();
    void runStartAction(CCPoint point, bool isUp, ChickenField* aRemoveChickenNode,int idx);
    void runGrapAction();
    void reSpawn();
private:
    CCSprite* masterSpr;
    ChickenField* removeChickenField;
    int removeIdx;
    bool isUp;
};
#endif