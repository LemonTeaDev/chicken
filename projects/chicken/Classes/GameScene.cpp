#include "GameScene.h"
#include "GameOverScene.h"
#include "Belt.h"
#include "Light.h"
#include "Master.h"
#include "CocosHelper.h"
#include "SoundManager.h"
#include "ChickenField.h"
#include "GameManager.h"
#include "StartScene.h"

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
	scene->addChild(layer, 0, 0);
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
    playBeltSound();
    
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
    CCSprite* fogSpr = CocosHelper::addSprite(this, "front-ef.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), GAME_SCENE_FOG,true,ccp(0.5f, 0.5f));
	fogSpr->setOpacity(128);

	// default player life is 3
	playerLife = 0;
	setPlayerLife(3);

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
#if 0
    CCScene* scene = GameOverScene::scene();
    CCDirector::sharedDirector()->replaceScene(scene);
#endif
    return true;
}
void GameScene::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchPoint = touch->getLocation();
}
void GameScene::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    
}
void GameScene::playBeltSound(){
    SoundManager::sharedSoundManager()->playBeltOneSound();
    runAction(CCSequence::create(CCDelayTime::create(SoundManager::sharedSoundManager()->beltSoundPitch),CCCallFunc::create(this, callfunc_selector(GameScene::playBeltSound)),NULL));
}
void GameScene::masterApper(){
    CCLog("MASTER APPEAR");
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    ChickenField* chickenField = (ChickenField*)getChildByTag(GAME_SCENE_CHICKEN);
    Chicken* dieChicken;
    if (rand() % 2 == 0){
        dieChicken = chickenField->GetMinHealthChicken();
        if (!dieChicken->GetIsCaptureAble()){
            dieChicken = chickenField->GetMaxHealthChicken();
        }
    }else{
        dieChicken = chickenField->GetMaxHealthChicken();
        if (!dieChicken->GetIsCaptureAble()){
            dieChicken = chickenField->GetMinHealthChicken();
        }
    }
    CCLog("dieChicken : %p",dieChicken );
    CCLog("dieChicken idx : %d",dieChicken->GetIdx() );
    if (dieChicken->GetIsCaptureAble()) {
        int idx = dieChicken->GetIdx()+1;
        CCNode* chickenLayer = chickenField->GetChickenNode(idx);
        CCPoint touchPoint = chickenLayer->getPosition();
        
        Master* master = Master::create();
        master->setAnchorPoint(ccp(0.5f,0.5f));
        if (touchPoint.y > visibleSize.height/2) {
            master->setPosition(touchPoint.x, visibleSize.height);
            addChild(master,GAME_SCENE_MASTER,GAME_SCENE_MASTER);
            master->runStartAction(touchPoint,true,chickenField,idx);
        }else{
            master->setPosition(touchPoint.x, 0);
            addChild(master,GAME_SCENE_MASTER,GAME_SCENE_MASTER);
            master->runStartAction(touchPoint,false,chickenField,idx);
        }
    }else{
        
    }
    
}

void GameScene::masterProgress(float dt){
    CCLabelBMFont* bmFont = (CCLabelBMFont*)getChildByTag(GAME_SCENE_TIME);
    char str[0x10];
    sprintf(str, "%d",(int)dt);
    if ((int)dt == 0) {
        bmFont->setString("");
    }else{
        bmFont->setString(str);
    }
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
void GameScene::speedUp(){
    Belt* belt = (Belt *)this->getChildByTag(GAME_SCENE_BELT);
    if(belt)
        belt->beltSpeedUp(10.0f);
}
void GameScene::speedDown(){
    Belt* belt = (Belt *)this->getChildByTag(GAME_SCENE_BELT);
    belt->beltSpeedDown(10.0f);
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

void GameScene::setPlayerLife(int life)
{
	if (playerLife == life)
	{
		return;
	}

	if (playerLife > life)
	{
		// decrease sprites
		int diff = playerLife - life;
		for (int i = 0; i < diff; ++i)
		{
			if (!lifeSprites.empty())
			{
				CCSprite* sprite = lifeSprites.back();
				sprite->removeFromParentAndCleanup(true);
				lifeSprites.pop_back();
			}
		}
	}
	else
	{
		// increase sprites
		int diff = life - playerLife;
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

		for (int i = 0; i < diff; ++i)
		{
			if (lifeSprites.empty())
			{
				CCSprite* pSprite = CocosHelper::addSprite(this, "life.png", CCPointMake(40, visibleSize.height - 30), GAME_SCENE_LIFE, true, ccp(0.5f, 0.5f));
				lifeSprites.push_back(pSprite);
			}
			else
			{
				unsigned int index = lifeSprites.size() - 1;
				auto lastSprite = lifeSprites[index];
				auto lastPosX = lastSprite->getPositionX();
				auto lastPosY = lastSprite->getPositionY();
				auto lastWidth = lastSprite->getContentSize().width;
				CCSprite* pSprite = CocosHelper::addSprite(this, "life.png", CCPointMake(lastPosX+lastWidth, lastPosY), GAME_SCENE_LIFE, true, ccp(0.5f, 0.5f));
				lifeSprites.push_back(pSprite);
			}
		}
	}

	playerLife = life;
	if (playerLife <= 0)
	{
		// Game Over
		CCScene* pScene = GameOverScene::scene();
		CCDirector::sharedDirector()->replaceScene(pScene);
	}
}

int GameScene::getPlayerLife() const
{
	return playerLife;
}
