#include "Character.h"
#include "Jump.h"

bool Jump::operator()(cocos2d::Sprite & sp, ActData & act)
{
	if (!act.jumpFlag)
	{
		act.jumpCnt = act.jumpMax;
		act.distance.y = 0;

		//	�W�����v�J�n
		if (act.key[UseKey::K_UP].first && act.key[UseKey::K_UP].second)
		{
			act.jumpFlag = true;
		}
	}

	if(act.jumpFlag)
	{
		//	jumpCnt�̐������W�����v�ł���悤�ɐ���
		if (act.distance.y == 0 && act.key[UseKey::K_UP].first)
		{
			act.jumpCnt--;
		}

		//	�����鏈��
		if (act.checkPoint[DIR::UP] || !act.key[UseKey::K_UP].first)
		{
			act.distance.y = 0;
		}
		//	�W�����v�\�񐔂𒴂��Ă��Ȃ�������W�����v����
		else if (act.jumpCnt >= -1)
		{
			act.distance.y = act.speed.y;
		}
	}
	return false;
}
