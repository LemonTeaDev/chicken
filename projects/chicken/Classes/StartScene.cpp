#include "StartScene.h"
#include "GameScene.h"
USING_NS_CC;

CCScene* StartScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    StartScene *layer = StartScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{

	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //window size
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin(); // left down corner


	
	
	CCMenuItemImage* pClose = CCMenuItemImage::create("quit_test.png", "quit_test.png", this, menu_selector(StartScene::menuCloseCallback));
	CCMenuItemImage* pStart = CCMenuItemImage::create("start_test.png", "start_test.png", this, menu_selector(StartScene::menuStartCallback));


	pClose->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	pStart->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - pClose->getContentSize().height));

	CCMenu* pMenu = CCMenu::create(pClose, pStart, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);
	/*
	
    //////////////////////////////
    // 1. super init first
  

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(StartScene::menuCloseCallback));
    
	pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

    // create menu, it's an autorelease object

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hey", "Arial", 24);
    
    // position the label on the center of the screen
    pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - pLabel->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(pLabel, 1);

    // add "StartScene" splash screen"
    CCSprite* pSprite = CCSprite::create("StartScene.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    */

    return true;
}


void StartScene::menuCloseCallback(CCObject* pSender)
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


void StartScene::menuStartCallback(CCObject* pSender)
{
	//shifts to start scene

	CCScene *pScene = GameScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);


}
