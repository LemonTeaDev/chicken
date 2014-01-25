#include "GameScene.h"
#include "GameOverScene.h"
#include "GameObjects/ChickenField.h"

USING_NS_CC;

CCScene* GameScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameScene *layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
	
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    this->addChild(pLabel, 1);

	ChickenField* pChickenField = ChickenField::create();
	this->addChild(pChickenField);


 //   CCSprite* pSprite = CCSprite::create("GameScene.png");
//    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

//    this->addChild(pSprite, 0);
    
    return true;
}


void GameScene::menuCloseCallback(CCObject* pSender)
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

void GameScene::menuGameOverCallback(CCObject* pSender)
{
	CCScene *pScene = GameOverScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

