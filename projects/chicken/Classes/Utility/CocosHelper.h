//
//  CocosHelper.h
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#ifndef __chicken__CocosHelper__
#define __chicken__CocosHelper__
#include <cocos2d.h>
USING_NS_CC;

class CocosHelper {
public:
    static CCSprite* addSprite(CCNode *parent, const char* filename, CCPoint position, int tag, bool isVisible = true, CCPoint anchor = ccp(0.5, 0.5),float scale = 1.0f);
     static CCSprite* addSpriteWithFrame(CCNode *parent, const char* frame, CCPoint position, int tag,bool isVisible = true,CCPoint anchor = ccp(0.5, 0.5),float scale = 1.0f);
};

#endif /* defined(__chicken__CocosHelper__) */
