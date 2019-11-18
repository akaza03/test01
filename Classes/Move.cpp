#include "Character.h"
#include "Move.h"

float Move::operator()(cocos2d::Sprite & sp, ActData & act)
{
	auto moveDistance = 0.0f;
	if (act.key[UseKey::K_LEFT].first && act.key[UseKey::K_LEFT].second)
	{
		if (!act.checkPoint[DIR::LEFT])
		{
			moveDistance -= act.speed;
		}
	}
	if (act.key[UseKey::K_RIGHT].first && act.key[UseKey::K_RIGHT].second)
	{
		if (!act.checkPoint[DIR::RIGHT])
		{
			moveDistance += act.speed;
		}
	}

	return moveDistance;

	//sp.setPosition(sp.getPosition().x + moveDistance, sp.getPosition().y);

	//if (moveDistance != 0.0f)
	//{
	//	return true;
	//}
	//return false;
}
