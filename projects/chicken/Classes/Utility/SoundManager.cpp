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
    this->audioEngine->setEffectsVolume(0.2f);
}

SoundManager::~SoundManager(){
    
}

SoundManager* SoundManager::sharedSoundManager(){
    if (onlySoundManager == NULL) {
        onlySoundManager = new SoundManager();
        onlySoundManager->preloadGameSound();
    }
    
    return onlySoundManager;
}

void SoundManager::preloadGameSound(){
    audioEngine->preloadEffect("belt_always.mp3");
}

void SoundManager::playGameBgm()
{
    audioEngine->playBackgroundMusic("bg_01.mp3", true);
}

void SoundManager::playBeltSound(){
    audioEngine->playEffect("belt_always.mp3", true);
}