#include "Character.h"
#include "Jump.h"

float Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto moveDistance = 0.0f;
	if (act.key[UseKey::K_UP].first && act.key[UseKey::K_UP].second)
	{
		if (!act.checkPoint[DIR::UP])
		{
			moveDistance += act.speed;
		}
	}

	return moveDistance;

	//sp.setPosition(sp.getPosition().x, sp.getPosition().y + moveDistance);

	//if (moveDistance != 0.0f)
	//{
	//	return true;
	//}
	//return false;
}
