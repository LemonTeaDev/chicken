// Chicken Game
// Chicken Field
// ltearain, 2014. 01. 25

#include "cocos2d.h"
#include "Chicken.h"
#include <array>
#include <memory>
#include <random>
USING_NS_CC;

class ChickenField : public CCLayer
{
public:
	static const int SLOT_COUNT = 8;
	static const int CHICKEN_SLOT_WIDTH = 127;
	static const int CHICKEN_SLOT_HEIGHT = 207;
	static const int CHICKEN_TAG = 999;

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(ChickenField)

public:
	typedef std::vector<int> IntVector;
	typedef std::shared_ptr<IntVector> IntVectorPtr;

	// index는 1부터 8까지!
	void AddChicken(int index, Chicken* chicken);
	Chicken* GetChicken(int index) const;
	void RemoveChicken(int index);

	// 빈 슬롯 찾기
	std::shared_ptr<IntVector> GetEmptySlots() const;
	int GetRandomEmptySlot() const;

	// 닭이 있는 슬롯 찾기
	std::shared_ptr<IntVector> GetFullSlots() const;
	int GetRandomFullSlot() const;

	// 닭이 있냐 없냐
	bool IsFull(int index) const;

private:
	int GetRealIndex(int humanIndex) const;
	void InitializeLayerCenterPos();

private:
	std::array<CCLayer*, SLOT_COUNT> chickenSlots;
	std::array<CCPoint, SLOT_COUNT> layerCenterPos;

	std::mt19937 randomEngine;
};