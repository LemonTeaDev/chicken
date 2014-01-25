//
//  SaveData.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__SaveData__
#define __chicken__SaveData__
#include <cocos2d.h>
USING_NS_CC;

class SaveData{
public:
    SaveData();
    ~SaveData();
    static SaveData* sharedSaveData();
    void saveData();
    void loadData();
    bool bgmOn;
    int score;
private:
    
};

#endif /* defined(__chicken__SaveData__) */
