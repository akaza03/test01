#include "Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	重力を加算する
	float gy = -0.05f;
	act.Gravity += gy;

	//	足場がある場合は重力を0に
	if (act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.jumpFlag = false;
	}

	//	空中でのめり込み防止処理
	if (act.Gravity != 0)
	{
		if (act.checkPoint[DIR::LEFT] && act.dir == DIR::LEFT)
		{
			act.distance.x = 0;
		}
		else if (act.checkPoint[DIR::RIGHT] && act.dir == DIR::RIGHT)
		{
			act.distance.x = 0;
		}
	}

	return false;
}
