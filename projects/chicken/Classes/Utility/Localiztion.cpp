//
//  Localiztion.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "Localiztion.h"
Localization* onlyLocalization = NULL;
Localization::Localization(){
    
}
Localization::~Localization(){
    
}

Localization* Localization::sharedLocalization(){
    if(onlyLocalization==NULL)
    {
        onlyLocalization = new Localization();
    }
    
    return onlyLocalization;
}

const char* Localization::getAppName(){
    if (mCurrentLanguage == kLanguageEnglish) {
        return "chicken game";
    }else if(mCurrentLanguage == kLanguageKorean){
        return "치킨게임";
    }
    return "";
}