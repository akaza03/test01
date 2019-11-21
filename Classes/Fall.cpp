#include "Character.h"
#include "Fall.h"

bool Fall::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	�d�͂����Z����
	float gy = -0.05f;
	act.Gravity += gy;

	//	���ꂪ����ꍇ�͏d�͂�0��
	if (act.checkPoint[DIR::DOWN])
	{
		act.Gravity = 0;
		act.skyflag = false;
	}

	return false;
}
