#include "Character.h"
#include "ActModule.h"

void ActModule::operator()(cocos2d::Sprite & sp, ActData & act)
{
	//	�����蔻��
	HitCheck()(sp, act);

	//	�ړ�����
	Jump()(sp, act);
	Move()(sp, act);
	Fall()(sp, act);

	//	�A�j���[�V�����̍X�V
	AnimUpdate()(sp, act);
	//	�����̍X�V
	DirCheck()(sp, act);
	//	�ړ�
	SetPos()(sp, act);
}
