#include "GameOverScene.h"
#include "GameScene.h"
#include "StartScene.h"
#include "CocosHelper.h"
//#include "layers_scenes_transitions_nodes\CCTransitionPageTurn.h"
#include "CCDirector.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CreditScene.h"
USING_NS_CC;

CCScene* GameOverScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	GameOverScene *layer = GameOverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!CCLayer::init())
	{
		return false;
	}
    
    SoundManager::sharedSoundManager()->playGameOverSound();
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //window size
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin(); // left down corner
    
	CCSprite* sprite = CCSprite::create("back-1.png");
	sprite->setPosition(ccp(visibleSize.width /2, visibleSize.height/2));
    sprite->setAnchorPoint(CCPointMake(0.5f, 0.5f));
	this->addChild(sprite,0);
    
    
    CCSprite* gameOverSpr = CocosHelper::addSprite(this, "gameover.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 1,true,ccp(0.5f, 0.5f),0.0f);
    gameOverSpr->runAction(CCSequence::create(CCScaleTo::create(0.5f, 1.0f),NULL));
    
    CCSprite* fogSpr = CocosHelper::addSprite(this, "front-ef.png", CCPointMake(visibleSize.width/2, visibleSize.height/2), 2,true,ccp(0.5f, 0.5f));
    fogSpr->setOpacity(0.85);

	CCMenuItemImage *pReplay = CCMenuItemImage::create("gameover_replaybt.png", "gameover_replaybt.png", this, menu_selector(GameOverScene::menuStartCallback));
    pReplay->setAnchorPoint(ccp(0.5f, 0.5f));
    pReplay->setScale(0.0F);
    pReplay->setTag(0);
    pReplay->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCScaleTo::create(0.5f, 1.0f),NULL));
	pReplay->setPosition(ccp(origin.x + visibleSize.width / 2-180, origin.y + visibleSize.height / 2-220));
    
    CCMenuItemImage *pCredit = CCMenuItemImage::create("credit_bt.png", "credit_bt.png", this, menu_selector(GameOverScene::menuStartCallback));
    pCredit->setAnchorPoint(ccp(0.5f, 0.5f));
    pCredit->setScale(0.0F);
    pCredit->setTag(1);
    pCredit->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCScaleTo::create(0.5f, 1.0f),NULL));
	pCredit->setPosition(ccp(origin.x + visibleSize.width / 2+180, origin.y + visibleSize.height / 2-220));
    
    //credit_bt
    
	CCMenu* pMenu = CCMenu::create(pReplay,pCredit, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

    char str[0x10];
    sprintf(str, "%d",GameManager::sharedGameManager()->getGameAccTime());
    CCLabelBMFont* font = CocosHelper::addLabelFnt(this, "single_pack_achievement_starpiece.fnt", ccp(visibleSize.width/2+200,200), 2, str, ccp(1.0f,0.5f), true);
    font->setScale(0.0f);
    font->runAction(CCSequence::create(CCDelayTime::create(1.0f),CCScaleTo::create(0.5f, 2.0f),NULL));
    
    CCLabelBMFont* font2 = CocosHelper::addLabelFnt(this, "friendinvite_reward_piece.fnt", ccp(visibleSize.width/2+220,200), 2, "s", ccp(0.5f,0.5f), true);
    font2->setScale(0.0f);
    font2->runAction(CCSequence::create(CCDelayTime::create(1.3f),CCScaleTo::create(0.5f, 2.0f),NULL));
    
	return true;
}

void GameOverScene::menuCloseCallback(CCObject* pSender)
{

}

void GameOverScene::menuStartCallback(CCObject* pSender)
{
    CCNode* node = (CCNode*)(pSender);
    if (node->getTag() == 0) {
        (node)->runAction(CCSequence::create(CCScaleTo::create(0.25f, 1.1f),CCScaleTo::create(0.25f, 1.0f),CCCallFunc::create(this, callfunc_selector(GameOverScene::menuStartAniEnd)),NULL));
    }else{
        CCScene *pScene = CreditScene::scene();
        CCDirector::sharedDirector()->pushScene(pScene);
    }
    
}
void GameOverScene::menuStartAniEnd(){
    CCScene *pScene = GameScene::scene();
	CCDirector::sharedDirector()->pushScene(pScene);
}