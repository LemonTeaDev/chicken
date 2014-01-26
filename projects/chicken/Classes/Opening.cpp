#include "Opening.h"


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

	background = CCSprite::create("op_first.png");
	background->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2));
	background->setScale(0.5f);
	this->addChild(background, 0);

	
	CCFiniteTimeAction* moveTo = CCMoveTo::create(1.0, ccp(visibleSize.width, origin.y));
	CCFiniteTimeAction* scaleTo = CCScaleTo::create(1.0, 1, 1);
	CCFiniteTimeAction* stop = CCMoveTo::create(2.0, ccp(visibleSize.width, origin.y));

	CCFiniteTimeAction* moveTo2 = CCMoveTo::create(1.0, ccp(visibleSize.width/2, visibleSize.height/2));
	CCFiniteTimeAction* scaleTo2 = CCScaleTo::create(1.0, 0.5, 0.5);

	CCFiniteTimeAction* moveTo3 = CCMoveTo::create(1.0, ccp(origin.x, origin.y));
	CCFiniteTimeAction* scaleTo3 = CCScaleTo::create(1.0, 1, 1);
	CCFiniteTimeAction* stop2 = CCMoveTo::create(1.0, ccp(origin.x, origin.y));

	CCSpawn* spawnOne = CCSpawn::create(moveTo, scaleTo,NULL);
	CCSpawn* spawnTwo = CCSpawn::create(moveTo2, scaleTo2, NULL);
	CCSpawn* spawnThr = CCSpawn::create(moveTo3, scaleTo3, NULL);

	CCSequence* seqOneBack = CCSequence::create(spawnOne, stop, spawnTwo, spawnThr, stop2, CCCallFunc::create(this,callfunc_selector(OpeningOne::seqOne)), NULL);

	background->runAction(seqOneBack);

	return true;
}


void OpeningOne::seqOne()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	if (AHandler == 1){


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

		CCSequence* seqOneBack = CCSequence::create(spawnOne, stop, spawnTwo, spawnThr, stop2, CCCallFunc::create(this, callfunc_selector(OpeningOne::seqOne)), NULL);

		background->runAction(seqOneBack);

	}
	else {

		CCFiniteTimeAction* stop2 = CCMoveTo::create(1.5, ccp(origin.x, origin.y));

		CCFiniteTimeAction* moveTo = CCMoveTo::create(1.0, ccp(visibleSize.width / 2, visibleSize.height / 2));
		CCFiniteTimeAction* scaleTo = CCScaleTo::create(1.0, 0.5, 0.5);

		CCFiniteTimeAction* stop = CCMoveTo::create(2.0, ccp(visibleSize.width, visibleSize.height));

		CCFiniteTimeAction* moveTo2 = CCMoveTo::create(1.0, ccp(visibleSize.width, visibleSize.height));
		CCFiniteTimeAction* scaleTo2 = CCScaleTo::create(1.0, 1.0, 1.0);

		CCSpawn* spawnOne = CCSpawn::create(moveTo, scaleTo, NULL);
		CCSpawn* spawnTwo = CCSpawn::create(moveTo2, scaleTo2, NULL);

		CCSequence* seqOneBack = CCSequence::create(stop2, spawnOne, spawnTwo, stop, NULL);
		background->runAction(seqOneBack);
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

			cloudAni->addSpriteFrameWithFileName("op_hungry.png");

			CCAnimate* animate = CCAnimate::create(cloudAni);
			cloud->runAction(animate);
		}
	}
}
