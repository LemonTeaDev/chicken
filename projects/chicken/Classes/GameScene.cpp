#include "GameScene.h"
#include "GameOverScene.h"
#include "GameObjects/Belt.h"
#include "GameObjects/Light.h"
#include "GameObjects/Master.h"
#include "Utility/CocosHelper.h"
#include "Utility/SoundManager.h"
#include "GameObjects/ChickenField.h"
#include "Utility/GameManager.h"

USING_NS_CC;
    
GameScene::GameScene()
{
    
}

GameScene::~GameScene()
{
    
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
    SoundManager::sharedSoundManager()->playGameBgm();
    SoundManager::sharedSoundManager()->playBeltSound();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    CCLog("%f %f",visibleSize.width, visibleSize.height);
    CocosHelper::addSprite(this, "back-1.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), GAME_SCENE_BG,true,ccp(0.5f, 0.5f));
    
    // conveyer belt + gears
    Belt* belt = Belt::create();
    addChild(belt,GAME_SCENE_BELT,GAME_SCENE_BELT);

    // lights
    Light* light = Light::create();
    light->setPosition(ccp(332, visibleSize.height-46));
    addChild(light,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    ChickenField* pChickenField = ChickenField::create();
    pChickenField->setPosition(ccp(0.0f, 0.0f));
    pChickenField->setAnchorPoint(ccp(0.5f, 0.5f));
	addChild(pChickenField,GAME_SCENE_CHICKEN,GAME_SCENE_CHICKEN);

    
    Light* light2 = Light::create();
    light2->setPosition(ccp(574, visibleSize.height-46));
    addChild(light2,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    Light* light3 = Light::create();
    light3->setPosition(ccp(803, visibleSize.height-46));
    addChild(light3,GAME_SCENE_LIGHT,GAME_SCENE_LIGHT);
    
    
    CocosHelper::addLabelFnt(this, "playui_fever_xcombo.fnt", ccp(visibleSize.width-100,100), GAME_SCENE_TIME, "", ccp(0.5f,0.5f), true);
    // dim background
    //CCSprite* fogSpr = CocosHelper::addSprite(this, "front-ef.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), GAME_SCENE_FOG,true,ccp(0.5f, 0.5f));
    /*
    CCSequence* sequence = CCSequence::create(CCMoveTo::create(5.0f, ccp(fogSpr->getPosition().x-100, fogSpr->getPosition().y)),CCMoveTo::create(5.0f, ccp(fogSpr->getPosition().x+100, fogSpr->getPosition().y)), NULL);
    fogSpr->runAction(CCRepeatForever::create(sequence));
    */
    
    /*
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
    */
    CCLog("this : %p",this);
    scheduleUpdateWithPriority(1);
    GameManager::sharedGameManager()->sendMessage(GameMessageGameStart);
    GameManager::sharedGameManager()->setMasterAppearListener(callfunc_selector(GameScene::masterApper), this);
    GameManager::sharedGameManager()->setMasterAppearProgressListener(schedule_selector(GameScene::masterProgress), this);
    return true;
}
void GameScene::onEnter(){
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCNode::onEnter();
}

void GameScene::update(float delta){
    GameManager *gm = GameManager::sharedGameManager();
    gm->update(delta);
}
bool GameScene::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    /*
    CCPoint touchPoint = touch->getLocation();
    Master* master = Master::create();
    master->setAnchorPoint(ccp(0.5f,0.5f));
    master->setPosition(ccp(touchPoint.x, touchPoint.y-40));
    
    CCSequence* sequence = CCSequence::create(CCMoveTo::create(0.2f, ccp(master->getPosition().x, master->getPosition().y+50)),CCCallFunc::create(master, callfunc_selector(Master::runGrapAction)), NULL);
    master->runAction(sequence);
    addChild(master,GAME_SCENE_MASTER,GAME_SCENE_MASTER);
     */
    return true;
}
void GameScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocation();
}
void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
}
void GameScene::masterApper(){
    CCLog("MASTER APPEAR");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    ChickenField* chickenField = (ChickenField*)getChildByTag(GAME_SCENE_CHICKEN);
    int randIdx = rand() % ChickenField::SLOT_COUNT + 1;
    CCNode* chickenLayer = chickenField->GetChickenNode(randIdx);
    
    CCPoint touchPoint = chickenLayer->getPosition();
    Master* master = Master::create();
    master->setAnchorPoint(ccp(0.5f,0.5f));
    if (touchPoint.y > visibleSize.height/2) {
        master->setPosition(touchPoint.x, visibleSize.height);
        addChild(master,GAME_SCENE_MASTER,GAME_SCENE_MASTER);
        master->runStartAction(touchPoint,true);
    }else{
        master->setPosition(touchPoint.x, 0);
        addChild(master,GAME_SCENE_MASTER,GAME_SCENE_MASTER);
        master->runStartAction(touchPoint,false);
    }
}

void GameScene::masterProgress(float dt){
    CCLabelBMFont* bmFont = (CCLabelBMFont*)getChildByTag(GAME_SCENE_TIME);
    char str[0x10];
    sprintf(str, "%d",(int)dt);
    bmFont->setString(str);
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
