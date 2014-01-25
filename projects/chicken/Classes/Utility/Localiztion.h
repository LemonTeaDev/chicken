//
//  Localiztion.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__Localiztion__
#define __chicken__Localiztion__

#include <cocos2d.h>
USING_NS_CC;


class Localization
{
public:
    Localization();
    ~Localization();
    
    static Localization* sharedLocalization();
    CC_SYNTHESIZE_READONLY(ccLanguageType, mCurrentLanguage, CurrentLanguage);
    const char* getAppName();
};

#endif /* defined(__chicken__Localiztion__) */
