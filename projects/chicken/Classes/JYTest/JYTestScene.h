//
//  JYTestScene.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__JYTestScene__
#define __chicken__JYTestScene__

#include "cocos2d.h"
#include "Belt.h"
class JYTestScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuStartCallback(CCObject* pSender);
    void menuReverseCallback(CCObject* pSender);
    // implement the "static node()" method manually
    CREATE_FUNC(JYTestScene);
    
    JYTestScene();
    ~JYTestScene();
private:
    Belt* belt;
};

#endif /* defined(__chicken__JYTestScene__) */
