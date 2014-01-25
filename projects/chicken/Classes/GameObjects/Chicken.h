#pragma  once
#include "cocos2d.h"
#include <map>
USING_NS_CC;

class Food;
typedef enum eChickenTag{
    CHICKEN_SPR,
    CHICKEN_MENU,
    CHICKEN_HEALTHBAR
}eChickenTag;
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
        max,
	};

    enum EventStatus
	{
		eat,
        cry
	};
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(Chicken)

public:
	virtual void update(float dt);	// �񸸵��� ���� sprite ������Ʈ ��, �ǽð� ������Ʈ ���
    void chickenTouch(CCObject* pSender);
    
	unsigned int GetLife() const;
    void UpdateHealthBar();
	void IncreaseLife(unsigned int delta);
	void DecreaseLife(unsigned int delta);
	void SetLife(unsigned int life);
	
	FatStatus GetFatStatus() const;

	// �� �ʿ� �� �� ��ȭ�� �ǰ� �� ���ΰ�?
	unsigned int GetDigestSpeed() const;
	void SetDigestSpeed(unsigned int speed);

	void Eat(Food* food);

	// �պ��� ġŲ�̳�, �ں��� ġŲ�̳�
	ChickenSide GetChickenSide() const;
	void SetChickenSide(ChickenSide chickenSide);
    void SetChickenEvent(EventStatus chickenEvent);
protected:
	virtual void InitializeLifeFatFactors();
	virtual void InitializeLifeMax();

protected:
	ChickenSide side;

	unsigned int life;
	unsigned int lifeMax;

    CCSprite* chickenSpr;
    CCSprite* healthSpr;
	std::map<FatStatus, CCTexture2D*> spriteFront;
	std::map<FatStatus, CCTexture2D*> spriteBack;
	std::map<FatStatus, CCTexture2D*> spriteFront_Eat;
	std::map<FatStatus, CCTexture2D*> spriteBack_Eat;
    std::map<FatStatus, CCTexture2D*> spriteFront_Cry;
	std::map<FatStatus, CCTexture2D*> spriteBack_Cry;
	mutable std::map<FatStatus, unsigned int> lifeFatFactor;
	
	unsigned int digestSpeed;
};