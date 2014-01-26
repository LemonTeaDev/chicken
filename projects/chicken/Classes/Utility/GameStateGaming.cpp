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
	accTime = 0;
    _state = eGameStateGaming;
    accTime = 0.0f;
    gameAccTime = 0.0f;
}
void GameStateGaming::update(float delta){
	if (accTime > INT_MAX)
	{
		accTime -= INT_MAX;
	}

    float tAccTime = accTime;
    accTime+=delta;
    gameAccTime+=delta;
    if ((int)tAccTime != (int)accTime) {
        GameManager::sharedGameManager()->masterProgress(GameManager::sharedGameManager()->getMasterApperTime()-accTime);
        GameManager::sharedGameManager()->setGameAccTime(gameAccTime);
    }
    if (accTime > GameManager::sharedGameManager()->getMasterApperTime()) {
        GameManager::sharedGameManager()->masterAppear();
        accTime = 0.0f;
    }
}