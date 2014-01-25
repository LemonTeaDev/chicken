// Chicken Game
// Chicken Field
// ltearain, 2014. 01. 25

#include "ChickenField.h"
#include <cassert>

/* virtual */ bool ChickenField::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	InitializeLayerCenterPos();

    int i = 0;

	for (auto slotItr = chickenSlots.begin(); slotItr != chickenSlots.end(); ++slotItr)
	{
		auto slot = *slotItr;
		slot = CCNode::create();
		slot->setContentSize(CCSizeMake(CHICKEN_SLOT_WIDTH, CHICKEN_SLOT_HEIGHT));
        slot->setAnchorPoint(ccp(0.0f, 0.0f));
		slot->setPosition(layerCenterPos[i]);
        
        Chicken* chicken = Chicken::create();
        if (i < 4) {
            chicken->SetChickenSide(Chicken::front);
        }else{
            chicken->SetChickenSide(Chicken::back);
        }
        chicken->SetIdx(i);
		slot->addChild(chicken,CHICKEN_TAG,CHICKEN_TAG);
        addChild(slot);
        *slotItr = slot;
		i++;
	}
	
	return true;
}

int ChickenField::GetRealIndex(int humanIndex) const
{
	int realIndex = humanIndex - 1;

	if (realIndex < 0)
	{
		assert(!"invalid index-");
		realIndex = 0;
	}
	else if (realIndex > SLOT_COUNT)
	{
		assert(!"invalid index+");
		realIndex = SLOT_COUNT;
	}

	return realIndex;
}

void ChickenField::InitializeLayerCenterPos()
{
	int i = 0;
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	layerCenterPos[i++] = CCPointMake(218, visibleSize.height-165);
	layerCenterPos[i++] = CCPointMake(468, visibleSize.height-165);
	layerCenterPos[i++] = CCPointMake(700, visibleSize.height-165);
	layerCenterPos[i++] = CCPointMake(938, visibleSize.height-165);
	layerCenterPos[i++] = CCPointMake(218, visibleSize.height-490);
	layerCenterPos[i++] = CCPointMake(468, visibleSize.height-490);
	layerCenterPos[i++] = CCPointMake(700, visibleSize.height-490);
	layerCenterPos[i++] = CCPointMake(938, visibleSize.height-490);
}

void ChickenField::AddChicken(int index, Chicken* chicken)
{
	if (chicken != nullptr)
	{
		chicken->setTag(CHICKEN_TAG);
		chickenSlots[GetRealIndex(index)]->addChild(chicken);
	}
}

Chicken* ChickenField::GetChicken(int index) const
{
    CCNode* node = chickenSlots[GetRealIndex(index)];
	return dynamic_cast<Chicken*>(
		node->getChildByTag(CHICKEN_TAG));
}
Chicken* ChickenField::GetMinHealthChicken() const{
    
    if (rand() % 2 == 0) {
        CCNode* node = *(chickenSlots.begin());
        Chicken* minChicken = (Chicken* )node->getChildByTag(CHICKEN_TAG);
        for (auto slotItr = chickenSlots.begin(); slotItr != chickenSlots.end(); ++slotItr)
        {
            auto slot = *slotItr;
            if (minChicken == NULL) {
                minChicken = (Chicken*)slot->getChildByTag(CHICKEN_TAG);
            }
            Chicken* chicken = (Chicken*)slot->getChildByTag(CHICKEN_TAG);
            if (chicken != NULL && minChicken != NULL && chicken->GetLife() < minChicken->GetLife()) {
                minChicken = chicken;
            }
        }
         return minChicken;
    }else{
        CCNode* node = *(chickenSlots.rbegin());
        Chicken* minChicken = (Chicken* )node->getChildByTag(CHICKEN_TAG);
        for (auto slotItr = chickenSlots.rbegin(); slotItr != chickenSlots.rend(); ++slotItr)
        {
            auto slot = *slotItr;
            if (minChicken == NULL) {
                minChicken = (Chicken*)slot->getChildByTag(CHICKEN_TAG);
            }
            Chicken* chicken = (Chicken*)slot->getChildByTag(CHICKEN_TAG);
            if (chicken != NULL && minChicken != NULL && chicken->GetLife() < minChicken->GetLife()) {
                minChicken = chicken;
            }
        }
         return minChicken;
    }

    return NULL;
}
CCNode* ChickenField::GetChickenNode(int index) const
{
    CCNode* node = chickenSlots[GetRealIndex(index)];
	return dynamic_cast<CCNode*>(node);
}
void ChickenField::RemoveChicken(int index)
{
	auto chicken = GetChicken(index);
	if (chicken != nullptr)
	{
		chicken->removeFromParentAndCleanup(true);
	}
}

bool ChickenField::IsFull(int index) const
{
	return (GetChicken(index) != nullptr);
}

ChickenField::IntVectorPtr ChickenField::GetEmptySlots() const
{
	IntVectorPtr resultVector(new ChickenField::IntVector());
	for (int i = 1; i <= SLOT_COUNT; ++i)
	{
		if (!IsFull(i))
		{
			resultVector->push_back(i);
		}
	}

	return resultVector;
}

ChickenField::IntVectorPtr ChickenField::GetFullSlots() const
{
	IntVectorPtr resultVector(new ChickenField::IntVector());
	for (int i = 1; i <= SLOT_COUNT; ++i)
	{
		if (IsFull(i))
		{
			resultVector->push_back(i);
		}
	}

	return resultVector;
}

int ChickenField::GetRandomEmptySlot() const
{
	// not found: 0
	auto emptySlotList = GetEmptySlots();
	if (emptySlotList->empty())
	{
		return 0;
	}
	else
	{
		std::uniform_int_distribution<int> dist(0, emptySlotList->size() - 1);
		return emptySlotList->at(dist(randomEngine));
	}
}

int ChickenField::GetRandomFullSlot() const
{
	// not found: 0
	auto fullSlotList = GetFullSlots();
	if (fullSlotList->empty())
	{
		return 0;
	}
	else
	{
		std::uniform_int_distribution<int> dist(0, fullSlotList->size() - 1);
		return fullSlotList->at(dist(randomEngine));
	}
}
