//
//  SoundManager.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__SoundManager__
#define __chicken__SoundManager__

#include <cocos2d.h>
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

class SoundManager{
public:
    SoundManager();
    ~SoundManager();
    static SoundManager* sharedSoundManager();
    //static SoundManager* sharedSoundManager();
    void preloadGameSound();
    void playGameBgm();
protected:
    CC_SYNTHESIZE(SimpleAudioEngine *, audioEngine, AudioEngine);
};

#endif /* defined(__chicken__SoundManager__) */
