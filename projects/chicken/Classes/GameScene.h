#pragma once

#include "cocos2d.h"
USING_NS_CC;
typedef enum eGameSceneTag{
    GAME_SCENE_BG,
    GAME_SCENE_BELT,
    GAME_SCENE_CHICKEN,
    GAME_SCENE_LIGHT,
    GAME_SCENE_FOG,
    GAME_SCENE_MASTER,
    GAME_SCENE_TIME,
    GAME_SCENE_MAX
}eGameSceneTag;

class GameScene : public cocos2d::CCLayer
{
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    virtual void onEnter();
    virtual void update(float delta);
    static cocos2d::CCScene* scene();
    
    
    bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    void ccTouchMoved(CCTouch* touch, CCEvent* event);
    void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
    void playBeltSound();
    void masterApper();
    void masterProgress(float dt);
    void menuCloseCallback(CCObject* pSender);
    void menuStartCallback(CCObject* pSender);
    void menuReverseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
    
private:
  
};


