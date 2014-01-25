//
//  GameStateNone.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__GameStateNone__
#define __chicken__GameStateNone__

#include "GameManager.h"

class GameStateNone : public GameState {
public:
    GameStateNone();
    virtual void update(float delta);
};


#endif /* defined(__chicken__GameStateNone__) */
