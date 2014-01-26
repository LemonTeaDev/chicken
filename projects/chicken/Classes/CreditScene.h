//
//  CreditScene.h
//  chicken
//
//  Created by Rangken on 2014. 1. 26..
//
//

#ifndef __chicken__CreditScene__
#define __chicken__CreditScene__
#include "cocos2d.h"
class CreditScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    // implement the "static node()" method manually
    CREATE_FUNC(CreditScene);
    
    CreditScene();
    ~CreditScene();
};

#endif /* defined(__chicken__CreditScene__) */
