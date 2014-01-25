#include "Chicken.h"
#include "Food.h"

/////////////////////////////////////////////////
// init
/////////////////////////////////////////////////
/* virtual */ bool Chicken::init()
{
	// Load Sprites
	spriteFront[slim] = CCSprite::create("../../Resources/normal_chicken_slim_f.png");
	spriteFront[normal] = CCSprite::create("../../Resources/normal_chicken_normal_f.png");
	spriteFront[fat] = CCSprite::create("../../Resources/normal_chicken_fat_f.png");
	spriteBack[slim] = CCSprite::create("../../Resources/normal_chicken_slim_b.png");
	spriteBack[normal] = CCSprite::create("../../Resources/normal_chicken_normal_b.png");
	spriteBack[fat] = CCSprite::create("../../Resources/normal_chicken_fat_b.png");

	InitializeLifeMax();
	InitializeLifeFatFactors();
	SetDigestSpeed(4);

	return true;
}

/////////////////////////////////////////////////
// life : fatness factor initialize
/////////////////////////////////////////////////
/* virtual */ void Chicken::InitializeLifeFatFactors()
{
	lifeFatFactor[slim] = 0;
	lifeFatFactor[normal] = 30;
	lifeFatFactor[fat] = 70;
}

/////////////////////////////////////////////////
// Get Fat Status according to the life
/////////////////////////////////////////////////
Chicken::FatStatus Chicken::GetFatStatus() const
{
	if (lifeFatFactor[slim] <= life &&
		life < lifeFatFactor[normal])
	{
		return slim;
	}
	else if (lifeFatFactor[normal] <= life &&
		life < lifeFatFactor[fat])
	{
		return normal;
	}
	else
	{
		return fat;
	}
}

//////////////////////////////////////////////////////
// set max life (value differs by the chicken species)
//////////////////////////////////////////////////////
/* virtual */ void Chicken::InitializeLifeMax()
{
	lifeMax = 100;
}

/////////////////////////////////////////////////
// Update Logic per Tick
/////////////////////////////////////////////////
/* virtual */ void Chicken::update(float dt)
{
	static float time = 0;
	time += dt;
	if (time > 10)
	{
		time -= 10;
	}

	if (static_cast<int>(time) % GetDigestSpeed() == 0)
	{
		DecreaseLife(1);
	}
}

unsigned int Chicken::GetLife() const
{
	return life;
}

void Chicken::IncreaseLife(unsigned int delta)
{
	if (life + delta > lifeMax)
	{
		life = lifeMax;
	}
	else
	{
		life += delta;
	}
}

void Chicken::DecreaseLife(unsigned int delta)
{
	if (life - delta > 0)
	{
		life -= delta;
	}
	else
	{
		life = 0;
	}
}

/////////////////////////////////////////////////
// nom nom nom nom
/////////////////////////////////////////////////
void Chicken::Eat(Food* food)
{
	// TODO implement this!
	// sprite animation ㄱㄱ
}

/////////////////////////////////////////////////
// Get Chicken's Looking side
/////////////////////////////////////////////////
Chicken::ChickenSide Chicken::GetChickenSide() const
{
	return side;
}

/////////////////////////////////////////////////
// Set Chicken's Looking side
/////////////////////////////////////////////////
void Chicken::SetChickenSide(ChickenSide chickenSide)
{
	side = chickenSide;
}

/////////////////////////////////////////////////
// 닭의 소화 속도. 몇 초에 한번 포만감이 감소하나
/////////////////////////////////////////////////
unsigned int Chicken::GetDigestSpeed() const
{
	return digestSpeed;
}

void Chicken::SetDigestSpeed(unsigned int speed)
{
	digestSpeed = speed;
}
