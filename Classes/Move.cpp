#include "Character.h""
#include "Move.h"

bool Move::operator()(cocos2d::Sprite & sp, CharaID & st)
{
	auto moveDistance = 0.0f;
	if (st.key[UseKey::K_RIGHT].first)
	{
		moveDistance += st.speed;
	}
	if (st.key[UseKey::K_LEFT].first)
	{
		moveDistance -= st.speed;
	}

	sp.setPosition(sp.getPosition().x + moveDistance, sp.getPosition().y);

	if (moveDistance != 0.0f)
	{
		return true;
	}
	return false;
}
