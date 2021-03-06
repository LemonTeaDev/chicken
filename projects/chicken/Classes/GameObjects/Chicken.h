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
	virtual void update(float dt);	// 비만도에 따른 sprite 업데이트 등, 실시간 업데이트 담당
    void chickenTouch(CCObject* pSender);
    
	int GetLife() const;
    void UpdateHealthBar();
	void IncreaseLife(unsigned int delta);
	void DecreaseLife(unsigned int delta);
	void Digest();
	void SetLife(int life);
    void SetIdx(unsigned int aIdx);
	unsigned int GetIdx() const;
	FatStatus GetFatStatus() const;
    bool GetIsCaptureAble();
	// 몇 초에 한 번 소화가 되게 할 것인가?
	unsigned int GetDigestSpeed() const;
	void SetDigestSpeed(unsigned int speed);
    
	void Eat(Food* food);

	// 앞보는 치킨이냐, 뒤보는 치킨이냐
	ChickenSide GetChickenSide() const;
	void SetChickenSide(ChickenSide chickenSide);
    void SetFatStatus();
    void SetChickenEvent(EventStatus chickenEvent);
protected:
	virtual void InitializeLifeFatFactors();
	virtual void InitializeLifeMax();

protected:
	ChickenSide side;

	int life;
	int lifeMax;
    unsigned int digestRange;
    unsigned int digestValue;
    
    unsigned int idx;
    CCSprite* chickenSpr;
    CCSprite* healthSpr;
	std::map<FatStatus, CCTexture2D*> spriteFront;
	std::map<FatStatus, CCTexture2D*> spriteBack;
	std::map<FatStatus, CCTexture2D*> spriteFront_Eat;
	std::map<FatStatus, CCTexture2D*> spriteBack_Eat;
    std::map<FatStatus, CCTexture2D*> spriteFront_Cry;
	std::map<FatStatus, CCTexture2D*> spriteBack_Cry;
	mutable std::map<FatStatus, int> lifeFatFactor;
	
	unsigned int digestSpeed;
};