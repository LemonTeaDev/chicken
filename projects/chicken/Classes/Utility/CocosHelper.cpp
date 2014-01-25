//
//  CocosHelper.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "CocosHelper.h"
#include <cassert>

CCSprite* CocosHelper::addSprite(CCNode *parent, const char* filename, CCPoint position, int tag, bool isVisible, CCPoint anchor ,float scale){
    CCSprite *child = CCSprite::create(filename);
    if (child == NULL)
    {
        CCLog("not found texture : %s",filename);
        child = CCSprite::create(filename);
    }
    //position.y = 360 - position.y;
    child->setPosition(position);
    child->setAnchorPoint(anchor);
    child->setScale(scale);
    parent->addChild(child, tag, tag);
    child->setVisible(isVisible);
    
    return child;
}

CCSprite* CocosHelper::addSpriteWithFrame(CCNode *parent, const char* filename, CCPoint position, int tag,bool isVisible,CCPoint anchor,float scale){
    CCSprite *child = CCSprite::createWithSpriteFrameName(filename);
    if (child == NULL)
    {
        CCLog("not found spriteframe : %s",filename);
        child = CCSprite::create(filename);
    }
    //position.y = 360 - position.y;
    child->setPosition(position);
    child->setAnchorPoint(anchor);
    child->setScale(scale);
    parent->addChild(child, tag, tag);
    child->setVisible(isVisible);
    
    return child;
}

CCPoint CocosHelper::getLeftTopPos(CCNode* node)
{
	if (node == nullptr)
	{
		assert(!"node null");
		return CCPointMake(0, 0);
	}
	else
	{
		auto anchorPoint = node->getAnchorPoint();
		auto contentSize = node->getContentSize();
		return CCPointMake(
			node->getPositionX() - (contentSize.width * anchorPoint.x),
			node->getPositionY() + (contentSize.height * (1 - anchorPoint.y)));
	}
}

CCPoint CocosHelper::getRightBottomPos(CCNode* node)
{
	if (node == nullptr)
	{
		assert(!"node null");
		return CCPointMake(0, 0);
	}
	else
	{
		auto anchorPoint = node->getAnchorPoint();
		auto contentSize = node->getContentSize();
		return CCPointMake(
			node->getPositionX() + (contentSize.width * (1 - anchorPoint.x)),
			node->getPositionY() - (contentSize.height * anchorPoint.y));
	}
}
