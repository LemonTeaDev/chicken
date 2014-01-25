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

	// index´Â 1ºÎÅÍ 8±îÁö!
	void AddChicken(int index, Chicken* chicken);
	Chicken* GetChicken(int index) const;
    CCNode* GetChickenNode(int index) const;
	void RemoveChicken(int index);

	// ºó ½½·Ô Ã£±â
	std::shared_ptr<IntVector> GetEmptySlots() const;
	int GetRandomEmptySlot() const;

	// ´ßÀÌ ÀÖ´Â ½½·Ô Ã£±â
	std::shared_ptr<IntVector> GetFullSlots() const;
	int GetRandomFullSlot() const;

	// ´ßÀÌ ÀÖ³Ä ¾ø³Ä
	bool IsFull(int index) const;

private:
	int GetRealIndex(int humanIndex) const;
	void InitializeLayerCenterPos();

private:
	std::array<CCNode*, SLOT_COUNT> chickenSlots;
	std::array<CCPoint, SLOT_COUNT> layerCenterPos;

	mutable std::mt19937 randomEngine;
};