//
//  GameManager.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "GameManager.h"
#include "GameStateNone.h"
#include "GameStateGaming.h"
#include "GameScene.h"
GameManager* onlyGameManager = NULL;

GameManager::GameManager(){
    
}

GameManager::~GameManager(){
    
}

GameManager* GameManager::sharedGameManager(){
    if (onlyGameManager == NULL) {
        onlyGameManager = new GameManager();
        onlyGameManager->init();
    }
    
    return onlyGameManager;
}
bool GameManager::init(){
    state = new GameStateNone;
    state->setModel(this);
    masterApperTime = 30.0F;
    return true;
}
void
GameManager::update(float delta)
{
    assert(state!=NULL);
    state->update(delta);
}
bool
GameManager::changeState(GameState *state)
{
    assert(state!=NULL);
    assert(this->state!=NULL);
    if(state->getModelState()==this->getGameState()) return false;
    
    delete this->state;
    this->state = state;
    
    state->setModel(this);
    return true;
}

void
GameManager::sendMessage(GameMessage message){
    switch (message) {
        case GameMessageInitBefore:
            
            break;
        case GameMessageGameStart:
            changeState(new GameStateGaming());
            break;
        default:
            break;
    }
}

void GameManager::setMasterAppearListener(SEL_CallFunc cb, CCNode* node){
    listener = node;
    masterAppearCB = cb;
}
void GameManager::setMasterAppearProgressListener(SEL_SCHEDULE cb, CCNode* node){
    listener = node;
    masterAppearProgressCB = cb;
}
void GameManager::masterAppear(){
    
    GameScene* scene = dynamic_cast<GameScene*>(listener);
    if (scene) {
        (scene->*masterAppearCB)();
    }
}
void GameManager::masterProgress(float dt){
    
    GameScene* scene = dynamic_cast<GameScene*>(listener);
    if (scene) {
        (scene->*masterAppearProgressCB)(dt);
    }
}