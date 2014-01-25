#pragma once

#include "cocos2d.h"
typedef enum eGameSceneTag{
    GAME_SCENE_BG,
    GAME_SCENE_BELT,
    GAME_SCENE_LIGHT,
    GAME_SCENE_FOG,
    GAME_SCENE_MAX
}eGameSceneTag;
class GameScene : public cocos2d::CCLayer
{
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    
    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);
    void menuStartCallback(CCObject* pSender);
    void menuReverseCallback(CCObject* pSender);
    CREATE_FUNC(GameScene);
    
private:
  
};


