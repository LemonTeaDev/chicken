//
//  CocosHelper.cpp
//  chicken
//
//  Created by Rangken on 2014. 1. 25..
//
//

#include "CocosHelper.h"

CCSprite* CocosHelper::addSprite(CCNode *parent, const char* filename, CCPoint position, int tag, bool isVisible, CCPoint anchor ,float scale){
    CCSprite *child = CCSprite::create(filename);
    if (child == NULL)
    {
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