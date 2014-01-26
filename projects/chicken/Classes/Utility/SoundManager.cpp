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
#if 1
    this->audioEngine->setEffectsVolume(0.5f);
    beltSoundPitch = 0.5f;
    //this->audioEngine->setEffectsVolume(0);
    //this->audioEngine->setBackgroundMusicVolume(0);
#endif
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
    audioEngine->preloadEffect("belt_one.mp3");
    audioEngine->preloadEffect("button.mp3");
    audioEngine->preloadEffect("create_chicken.mp3");
    audioEngine->preloadEffect("eat_fail.mp3");
    audioEngine->preloadEffect("eat.mp3");
    audioEngine->preloadEffect("footstep.mp3");
    audioEngine->preloadEffect("gameover.mp3");
    audioEngine->preloadEffect("hand.mp3");
    audioEngine->preloadEffect("hand.mp3");
    audioEngine->preloadEffect("get_item.mp3");
}

void SoundManager::playGameBgm()
{
    audioEngine->stopBackgroundMusic();
    audioEngine->playBackgroundMusic("bg_01.mp3", true);
}
void SoundManager::playTitleBgm(){
    audioEngine->stopBackgroundMusic();
    audioEngine->playBackgroundMusic("title.mp3", true);
}
void SoundManager::playBeltSound(){
    audioEngine->playEffect("belt_always.mp3", false);
}

void SoundManager::playBeltOneSound(){
    audioEngine->playEffect("belt_one.mp3", false);
}
void SoundManager::playButtonSound(){
    audioEngine->playEffect("button.mp3", false);
}
void SoundManager::playCreateChickenSound(){
    audioEngine->playEffect("create_chicken.mp3", false);
}
void SoundManager::playEatFailSound()
{
    audioEngine->playEffect("eat_fail.mp3", false);
}
void SoundManager::playEatSound(){
    audioEngine->playEffect("eat.mp3", false);
}
void SoundManager::playItemSound(){
    audioEngine->playEffect("get_item.mp3", false);
}
void SoundManager::playGameOverSound(){
    audioEngine->playEffect("gameover.mp3", false);
}
void SoundManager::playHandSound(){
    audioEngine->playEffect("hand.mp3", false);
}
