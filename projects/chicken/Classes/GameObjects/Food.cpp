#include "Food.h"
#include "Belt.h"

/* virtual */
bool Food::init()
{
	// super init
	if (!CCNode::init())
	{
		return false;
	}

	scheduleUpdate();
	return true;
}

/* virtual */
void Food::removeFromParentAndCleanup(bool cleanup)
{
	auto parent = dynamic_cast<Belt*>(getParent());
	if (parent != nullptr)
	{
		parent->unloadFood(this, cleanup);
	}
}

/* virtual */
void Food::update(float dt)
{
	// TODO 화면 밖으로 나갔는지 체크해서 나간 경우 제거한다.
	// 단, 정방향이든 역방향이든 첨에 음식이 추가될 때는 화면 밖에서 시작하도록 하고
	// 그 위치는 체크하지 않는다
}