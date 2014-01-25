//
//  GameManager.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__GameManager__
#define __chicken__GameManager__

#include <cocos2d.h>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;
enum eGameState
{
    eGameStateNone = 0,
    eGameStateGaming ,
    eGameStateCalculateScore,
    eGameStateStar,
};

class GameManager;
struct GameState
{
    virtual void update(float delta) = 0;
protected:
    CC_SYNTHESIZE(eGameState, _state, ModelState);
    CC_SYNTHESIZE(GameManager *, _model, Model);
};
enum GameMessage
{
    GameMessageInitBefore = 0x00,
    GameMessageGameStart,
    GameMessageGameMAX
};
class GameManager{
public:
    GameManager();
    ~GameManager();
    void update(float delta);
    static GameManager* sharedGameManager();
    bool init();
    bool changeState(GameState *state);
    void sendMessage(GameMessage message);
    
    CC_SYNTHESIZE_READONLY(eGameState, _NOT_USE9, GameState);
    CC_SYNTHESIZE(float, masterApperTime, MasterApperTime);
    
    void setMasterAppearListener(SEL_CallFunc cb, CCNode* node);
    void setMasterAppearProgressListener(SEL_SCHEDULE cb, CCNode* node);
    void masterAppear();
    void masterProgress(float dt);
protected:
    SEL_CallFunc masterAppearCB;
    SEL_SCHEDULE masterAppearProgressCB;
    CCObject* listener;
private:
    GameState *state;
	
    //CC_SYNTHESIZE(SimpleAudioEngine *, audioEngine, AudioEngine);
};

#endif /* defined(__chicken__GameManager__) */
