
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
	
	void menuStartCallback();

private :

	int AHandler;
	int BHandler;

	cocos2d::CCSprite* background;

	cocos2d::CCSprite* cloud;

	cocos2d::CCSprite* effect1;
	cocos2d::CCSprite* effect2;


	CREATE_FUNC(OpeningOne);
};

#endif
