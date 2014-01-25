#include "GameScene.h"
#include "GameOverScene.h"
#include "Belt.h"
#include "Light.h"
#include "CocosHelper.h"
USING_NS_CC;
GameScene::GameScene(){
    
}
GameScene::~GameScene(){
    
}
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
    if ( !CCLayer::init() )
    {
        return false;
    }
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
    CCLog("%f %f",visibleSize.width, visibleSize.height);
    CocosHelper::addSprite(this, "back-1.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), GAME_SCENE_BG,true,ccp(0.5f, 0.5f));
    
    // 컨베이어 벨트
    Belt* belt = Belt::create();
    addChild(belt,GAME_SCENE_BELT,GAME_SCENE_BELT);
    
    // 불빛들
    Light* light = Light::create();
    light->setPosition(ccp(332, visibleSize.height-46));
    addChild(light,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    Light* light2 = Light::create();
    light2->setPosition(ccp(574, visibleSize.height-46));
    addChild(light2,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    Light* light3 = Light::create();
    light3->setPosition(ccp(803, visibleSize.height-46));
    addChild(light3,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    // 희미한 배경
    /*
    CCSprite* fogSpr = CocosHelper::addSprite(this, "Front-ef.jpg", CCPointMake(visibleSize.width/2, visibleSize.height/2), GAME_SCENE_FOG,true,ccp(0.5f, 0.5f));
    CCSequence* sequence = CCSequence::create(CCMoveTo::create(5.0f, ccp(fogSpr->getPosition().x-100, fogSpr->getPosition().y)),CCMoveTo::create(5.0f, ccp(fogSpr->getPosition().x+100, fogSpr->getPosition().y)), NULL);
    fogSpr->runAction(CCRepeatForever::create(sequence));
    */
    
    CCMenuItem* pUp = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(GameScene::menuCloseCallback));
	pUp->setTag(1);
    CCMenuItem* pDown = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(GameScene::menuCloseCallback));
    pDown->setTag(2);
    CCMenuItem* pReverse = CCMenuItemImage::create("Icon-114.png", "Icon-114.png", this, menu_selector(GameScene::menuCloseCallback));
    pReverse->setTag(3);
    
	pUp->setPosition(ccp(50, origin.y + visibleSize.height / 2));
	pDown->setPosition(ccp(50, origin.y + visibleSize.height / 2 - pUp->getContentSize().height-30));
    pReverse->setPosition(ccp(50, origin.y + visibleSize.height / 2 - pUp->getContentSize().height-150));
    CCArray* menuItemArr = CCArray::create(pUp,pDown,pReverse,NULL);
	CCMenu* pMenu = CCMenu::createWithArray(menuItemArr);
    
    pMenu->setPosition(CCPointZero);
	addChild(pMenu, 1);
    
    CCLog("this : %p",this);
    return true;
}
void GameScene::menuCloseCallback(CCObject* pSender)
{
    CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
    
	int tag = (int)pMenuItem->getTag();
    CCLog("TAG : %d",tag);
    if (tag == 1) {
        CCMenu* menu = (CCMenu*)pMenuItem->getParent();
        GameScene* scene = (GameScene*)menu->getParent();
        Belt* belt = (Belt *)scene->getChildByTag(GAME_SCENE_BELT);
        belt->beltSpeedUp(10.0f);
    }else if (tag == 2){
        CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
        GameScene* scene = (GameScene*)menu->getParent();
        Belt* belt = (Belt *)scene->getChildByTag(GAME_SCENE_BELT);
        belt->beltSpeedDown(10.0f);
    }else if(tag == 3){
        CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
        GameScene* scene = (GameScene*)menu->getParent();
        Belt* belt = (Belt *)scene->getChildByTag(GAME_SCENE_BELT);
        belt->beltReverse();
    }
}

void GameScene::menuStartCallback(CCObject* pSender)
{
    CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
    GameScene* scene = (GameScene*)menu->getParent();
    Belt* belt = (Belt *)scene->getChildByTag(GAME_SCENE_BELT);
    belt->beltSpeedUp(10.0f);
}
void GameScene::menuReverseCallback(CCObject* pSender)
{
    CCMenu* menu = (CCMenu*)(((CCNode*)(pSender))->getParent());
    GameScene* scene = (GameScene*)menu->getParent();
    Belt* belt = (Belt *)scene->getChildByTag(GAME_SCENE_BELT);
    belt->beltReverse();
}
