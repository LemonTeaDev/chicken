
#ifndef __OPENING_ONE__H
#define __OPENING_ONE__H

#include "cocos2d.h"

USING_NS_CC;

class OpeningOne : public cocos2d::CCLayer
{
public:
	
	virtual bool init();
	static cocos2d::CCScene* scene();

	void seqOne();
	void seqTwo();
	void seqThr();
	void seqFor();

private :

	int AHandler;
	int BHandler;
	int CHandler;

	cocos2d::CCSprite* background;

	cocos2d::CCSprite* cloud;

	cocos2d::CCSprite* effect1;
	cocos2d::CCSprite* effect2;
	cocos2d::CCSprite* effect3;

	cocos2d::CCSprite* door1;
	cocos2d::CCSprite* door2;

	CREATE_FUNC(OpeningOne);
};

#endif
