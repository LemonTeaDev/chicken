//
//  SaveData.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "SaveData.h"
#include <string>
#define   SAVE_FILE_NAME  "save.dat"
using namespace std;

SaveData* onlySaveData;

SaveData::SaveData(){
    
}
SaveData::~SaveData(){
    
}
SaveData* SaveData::sharedSaveData(){
    if (onlySaveData == NULL) {
        onlySaveData = new SaveData();
    }
    return onlySaveData;
}

void SaveData::saveData(){
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + SAVE_FILE_NAME;
    CCLog("path : %s",path.c_str());
    FILE *pFile = fopen(path.c_str(), "wb");
    
    size_t size = sizeof(SaveData);
    size_t readSize = 0;
    fseek( pFile, 0, SEEK_END );
    long originalSize = ftell(pFile); // 얼레 파일 크기.
    fseek( pFile, 0, SEEK_SET );

    if(pFile)
    {
        while (size>0) {
            readSize= fwrite(this, 1, size, pFile);
            assert(readSize!=-1);
            size -= readSize;
        }
        fclose(pFile);
    }
    
}
void SaveData::loadData(){
    string path = CCFileUtils::sharedFileUtils()->getWritablePath() + SAVE_FILE_NAME;
    FILE *pFile = fopen(path.c_str(), "rb");
    
    size_t size = sizeof(SaveData);
    size_t readSize = 0;
    
    if (pFile)
    {
        fseek( pFile, 0, SEEK_END );
        long originalSize = ftell(pFile); // 얼레 파일 크기.
        fseek( pFile, 0, SEEK_SET );
        
        while (originalSize>0) {
            readSize = fread(this, 1, originalSize, pFile);
            assert(readSize!=-1);
            assert(readSize!=0);
            originalSize -= readSize;
        }
        fclose(pFile);
    }
}