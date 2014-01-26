#include "Opening.h"
#include "StartScene.h"


CCScene* OpeningOne::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	OpeningOne *layer = OpeningOne::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;

}

bool OpeningOne::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	AHandler = 0;
	BHandler = 0;
	background = CCSprite::create("op_first.png");
	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(0.5f);
	this->addChild(background, 0);

	cloud = CCSprite::create("blank.png");
	cloud->setPosition(ccp(visibleSize.width / 2 - 80.0, visibleSize.height / 2 + 150.0));
	this->addChild(cloud, 1);

	effect1 = CCSprite::create("blank.png");
	effect1->setPosition(ccp(visibleSize.width / 2 - 200.0, visibleSize.height / 2 - 200.0));
	effect1->setScale(0.6f);
	this->addChild(effect1, 1);

	effect2 = CCSprite::create("blank.png");
	effect2->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	effect2->setScale(1.0f);
	this->addChild(effect2, 1);


	seqOne();
	return true;
}


void OpeningOne::seqOne()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	switch(AHandler){

	case 0:{

			   CCFiniteTimeAction* moveTo = CCMoveTo::create(1.0, ccp(visibleSize.width, origin.y));
			   CCFiniteTimeAction* scaleTo = CCScaleTo::create(1.0, 1, 1);
			   CCFiniteTimeAction* stop = CCMoveTo::create(2.0, ccp(visibleSize.width, origin.y));

			   CCFiniteTimeAction* moveTo2 = CCMoveTo::create(1.0, ccp(visibleSize.width / 2, visibleSize.height / 2));
			   CCFiniteTimeAction* scaleTo2 = CCScaleTo::create(1.0, 0.5, 0.5);

			   CCFiniteTimeAction* moveTo3 = CCMoveTo::create(1.0, ccp(origin.x, origin.y));
			   CCFiniteTimeAction* scaleTo3 = CCScaleTo::create(1.0, 1, 1);
			   CCFiniteTimeAction* stop2 = CCMoveTo::create(1.0, ccp(origin.x, origin.y));

			   CCSpawn* spawnOne = CCSpawn::create(moveTo, scaleTo, NULL);
			   CCSpawn* spawnTwo = CCSpawn::create(moveTo2, scaleTo2, NULL);
			   CCSpawn* spawnThr = CCSpawn::create(moveTo3, scaleTo3, NULL);

			   AHandler++;

			   CCSequence* seqOneBack = CCSequence::create(spawnOne, stop, spawnTwo, spawnThr, stop2, CCCallFunc::create(this, callfunc_selector(OpeningOne::seqTwo)), NULL);

			   background->runAction(seqOneBack);
	}break;


	case 1: {

				CCFiniteTimeAction* stop2 = CCMoveTo::create(1.5, ccp(origin.x, origin.y));

				CCFiniteTimeAction* moveTo = CCMoveTo::create(1.0, ccp(visibleSize.width / 2, visibleSize.height / 2));
				CCFiniteTimeAction* scaleTo = CCScaleTo::create(1.0, 0.5, 0.5);

				CCFiniteTimeAction* stop = CCMoveTo::create(2.0, ccp(visibleSize.width, visibleSize.height));

				CCFiniteTimeAction* moveTo2 = CCMoveTo::create(1.0, ccp(visibleSize.width, visibleSize.height));
				CCFiniteTimeAction* scaleTo2 = CCScaleTo::create(1.0, 1.0, 1.0);

				CCFiniteTimeAction* moveTo3 = CCMoveTo::create(1.0, ccp(visibleSize.width / 2, visibleSize.height / 2));
				CCFiniteTimeAction* scaleTo3 = CCScaleTo::create(1.0, 0.5, 0.5);

				CCSpawn* spawnOne = CCSpawn::create(moveTo, scaleTo, NULL);
				CCSpawn* spawnTwo = CCSpawn::create(moveTo2, scaleTo2, NULL);
				CCSpawn* spawnThr = CCSpawn::create(moveTo3, scaleTo3, NULL);

				CCSequence* seqOneBack = CCSequence::create(stop2, spawnOne, spawnTwo, stop, spawnThr, CCCallFunc::create(this, callfunc_selector(OpeningOne::seqTwo)), NULL);
				


				AHandler++;

				background->runAction(seqOneBack);
	

	}break;

	case 2: {

			CCFiniteTimeAction* stop = CCMoveTo::create(1.5, ccp(visibleSize.width / 2, visibleSize.height / 2));

			CCFiniteTimeAction* moveTo = CCMoveTo::create(1.0, ccp(origin.x, visibleSize.height));
			CCFiniteTimeAction* scaleTo = CCScaleTo::create(1.0, 1.0, 1.0);

			CCSpawn* spawnOne = CCSpawn::create(moveTo, scaleTo, NULL);

			CCSequence* seqOneBack = CCSequence::create(stop, spawnOne, CCCallFunc::create(this, callfunc_selector(OpeningOne::seqTwo)), NULL);

			background->runAction(seqOneBack);


	}break;

	}
}

void OpeningOne::seqTwo()
{
	switch (BHandler)
	{
		case 0:
		{
			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
			CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

			CCAnimation* cloudAni = CCAnimation::create();
			cloudAni->setDelayPerUnit(3.0f / 2.0f);
			cloudAni->setRestoreOriginalFrame(true);

			cloudAni->addSpriteFrameWithFileName("op_hungry.png");

			BHandler++;

			CCAnimate* animate = CCAnimate::create(cloudAni);
			cloud->runAction(animate);

			seqOne();
		}break;

		case 1:
		{

		 CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		 CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		 CCAnimation* effectAni = CCAnimation::create();
		 effectAni->setDelayPerUnit(3.0f / 2.0f);
		 effectAni->setRestoreOriginalFrame(true);

		 effectAni->addSpriteFrameWithFileName("op_ef1.png");

		BHandler++;

		CCFiniteTimeAction* moveTo = CCMoveTo::create(0.5, ccp(visibleSize.width / 2, visibleSize.height / 2));
		
     	 CCAnimate* animate = CCAnimate::create(effectAni);
		 CCSpawn* seqTwoBack = CCSpawn::create(moveTo, animate, NULL);
		 effect1->runAction(seqTwoBack);

		seqOne();

		}break;

		case 2:

		{

			CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
			CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

		    CCAnimation* effectAni = CCAnimation::create();
			effectAni->setDelayPerUnit(3.0f / 2.0f);

			effectAni->addSpriteFrameWithFileName("op_door2.png");

			BHandler++;

		    CCAnimate* animate = CCAnimate::create(effectAni);

			CCSequence* seqTwoBack = CCSequence::create(animate, CCCallFunc::create(this, callfunc_selector(OpeningOne::menuStartCallback)), NULL);
		   effect2->runAction(seqTwoBack);


		}
	}
}

void OpeningOne::menuStartCallback()
{
	CCScene* pScene = StartScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}
