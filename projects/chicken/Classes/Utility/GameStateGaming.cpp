//
//  GameStateGaming.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "GameStateGaming.h"
#include "GameManager.h"
GameStateGaming::GameStateGaming(){
    _state = eGameStateGaming;
}
void GameStateGaming::update(float delta){
    float tAccTime = accTime;
    accTime+=delta;
    if ((int)tAccTime != (int)accTime) {
        GameManager::sharedGameManager()->masterProgress(GameManager::sharedGameManager()->getMasterApperTime()-accTime);
    }
    if (accTime > GameManager::sharedGameManager()->getMasterApperTime()) {
        GameManager::sharedGameManager()->masterAppear();
        accTime = 0.0f;
    }
}