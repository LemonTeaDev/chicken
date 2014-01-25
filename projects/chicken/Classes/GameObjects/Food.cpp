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
	// TODO ȭ�� ������ �������� üũ�ؼ� ���� ��� �����Ѵ�.
	// ��, �������̵� �������̵� ÷�� ������ �߰��� ���� ȭ�� �ۿ��� �����ϵ��� �ϰ�
	// �� ��ġ�� üũ���� �ʴ´�
}