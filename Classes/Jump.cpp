#include "Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, CharaID & st)
{
	auto moveDistance = 0.0f;
	if (st.key[UseKey::K_UP].first)
	{
		moveDistance += st.speed;
	}
	if (st.key[UseKey::K_DOWN].first)
	{
		moveDistance -= st.speed;
	}

	sp.setPosition(sp.getPosition().x, sp.getPosition().y + moveDistance);

	if (moveDistance != 0.0f)
	{
		return true;
	}
	return false;
}
