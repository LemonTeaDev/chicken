#pragma once

#include "cocos2d.h"

class GameOverScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
	void menuStartCallback(CCObject* pSender);
    void menuStartAniEnd();
    // implement the "static node()" method manually
    CREATE_FUNC(GameOverScene);
};
