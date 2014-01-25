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
        //DFLocalization::sharedLocalization()->mCurrentLanguage = kLanguageKorean;
    }
    
    return onlyLocalization;
}