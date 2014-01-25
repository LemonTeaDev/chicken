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
using namespace cocos2d;


class Localization
{
public:
    Localization();
    ~Localization();
    
    static Localization* sharedLocalization();
    CC_SYNTHESIZE_READONLY(ccLanguageType, mCurrentLanguage, CurrentLanguage);
};

#endif /* defined(__chicken__Localiztion__) */
