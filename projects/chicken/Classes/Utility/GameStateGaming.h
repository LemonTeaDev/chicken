//
//  GameStateGaming.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__GameStateGaming__
#define __chicken__GameStateGaming__

#include "GameManager.h"

class GameStateGaming : public GameState {
public:
    GameStateGaming();
    virtual void update(float delta);
private:
    float accTime;
    float gameAccTime;
};


#endif /* defined(__chicken__GameStateGaming__) */
