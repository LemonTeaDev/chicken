#include "HelloWorldScene.h"
#include "CocosHelper.h"

USING_NS_CC;
HelloWorld::HelloWorld(){
    CCTextureCache::sharedTextureCache()->addImage("Icon-114.png");
    CCTextureCache::sharedTextureCache()->addImage("Icon-144.png");
    CCTextureCache::sharedTextureCache()->addImage("Icon-57.png");
}

HelloWorld::~HelloWorld(){
    
}
CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCSprite* spr = CocosHelper::addSprite(this, "Icon-114.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 0);
    
    CCAnimation* anim = CCAnimation::create();
    anim->setDelayPerUnit(0.3f);
    anim->addSpriteFrameWithFileName("Icon-114.png");
    anim->addSpriteFrameWithFileName("Icon-144.png");
    anim->addSpriteFrameWithFileName("Icon-57.png");
    
    
    CCAnimate *animate = CCAnimate::create(anim);
    spr->runAction(CCRepeatForever::create(animate));
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
