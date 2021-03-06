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
	static CCPoint getLeftTopPos(CCNode* node);
	static CCPoint getRightBottomPos(CCNode* node);
    static CCLabelBMFont* addLabelFnt(CCNode *parent, const char* fontFile, CCPoint position, int tag, const char* str, CCPoint anchor, bool autoSize);
};

#endif /* defined(__chicken__CocosHelper__) */
