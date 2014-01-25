#pragma  once
#include "cocos2d.h"
#include <map>
USING_NS_CC;

class Food;

class Chicken : public CCNode
{
public:
	enum ChickenSide
	{
		front,
		back,
	};

	enum FatStatus
	{
		slim,
		normal,
		fat,
	};

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(Chicken)

public:
	virtual void update(float dt);	// �񸸵��� ���� sprite ������Ʈ ��, �ǽð� ������Ʈ ���

	unsigned int GetLife() const;
	void IncreaseLife(unsigned int delta);
	void DecreaseLife(unsigned int delta);
	
	FatStatus GetFatStatus() const;

	// �� �ʿ� �� �� ��ȭ�� �ǰ� �� ���ΰ�?
	unsigned int GetDigestSpeed() const;
	void SetDigestSpeed(unsigned int speed);

	void Eat(Food* food);

	// �պ��� ġŲ�̳�, �ں��� ġŲ�̳�
	ChickenSide GetChickenSide() const;
	void SetChickenSide(ChickenSide chickenSide);

protected:
	virtual void InitializeLifeFatFactors();
	virtual void InitializeLifeMax();

protected:
	ChickenSide side;

	unsigned int life;
	unsigned int lifeMax;

	std::map<FatStatus, CCSprite*> spriteFront;
	std::map<FatStatus, CCSprite*> spriteBack;

	mutable std::map<FatStatus, unsigned int> lifeFatFactor;
	
	unsigned int digestSpeed;
};