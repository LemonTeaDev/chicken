//
//  SoundManager.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "SoundManager.h"

SoundManager* onlySoundManager = NULL;

SoundManager::SoundManager(){
    this->audioEngine = SimpleAudioEngine::sharedEngine();
}

SoundManager::~SoundManager(){
    
}

SoundManager* SoundManager::sharedSoundManager(){
    if (onlySoundManager == NULL) {
        onlySoundManager = new SoundManager();
    }
    return onlySoundManager;
}

void SoundManager::preloadGameSound(){
    audioEngine->preloadEffect("botton.mp3");
}

void SoundManager::playGameBgm()
{
    audioEngine->playBackgroundMusic("bg_01.mp3", true);
}