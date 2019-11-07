#include "Player.h"

Player::Player()
{
	_charaID.cType = CharaType::PLAYER;

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	for (auto itr : _charaList)
	{
		//	�L�[�̃`�F�b�N
		auto checkKey = _oprtState->GetKeyCode();

		//	���̃L�[���}�b�v�ɂ��邩����(0�Ȃ瑶�݂��Ȃ�)
		if (itr.second.key.count(checkKey) != 0)
		{

			//	�������ꍇ��now��true��
			itr.second.key[checkKey].first = true;

			//	now != old
			if (itr.second.key[checkKey].first != itr.second.key[checkKey].second)
			{

			}
		}

		//	�����蔻��
		if (HitCheck()(*this, itr.second))
		{
			//itr.
			//itr.second.speed = 0;
		}

		//	�A�j���[�V�����̍X�V
		if (itr.second.anim != _oldState)
		{
			lpAnimManager.AnimRun(this, itr.second.anim, itr.second.cType);
		}

		//	�L�[�̍X�V
		for (auto keyItr : itr.second.key)
		{
			//	old = now
			keyItr.second.second = keyItr.second.first;
		}
	}



//	//	�����蔻�菈��
//	CheckCol();
//	//	�d�͂����W�ɉ��Z����
//	setPosition(getPosition().x, getPosition().y + _Gravity);
//	//	�f�o�b�O�pBox�̍��W�ݒ�
//#ifdef _DEBUG
//	_box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
//	_box->setPosition(getPosition());
//#endif // _DEBUG
//
//	//	�����̍X�V
//	dirUpdate();
//	//	�ړ��̍X�V
//	moveUpdate();
//	//	�A�j���[�V�����̍X�V
//	AnimStateUpdate();
}

void Player::SetCharaType()
{
	for (auto itr : _charaList)
	{
		itr.second.cType = CharaType::PLAYER;
	}
}

