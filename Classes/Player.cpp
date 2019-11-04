#include "Player.h"

Player::Player()
{
	_state = AnimState::IDLE;
	_oldState = AnimState::STATE_MAX;
	_movePos = cocos2d::Vec2(0, 0);
	_cType = CharaType::PLAYER;

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	for (auto itr:_charaList)
	{
		//input[] = 0 or 1;
		//nowKey[] = input[];
		//oldKey[] = nowKey[];
		//if (oldKey[] != nowKey[])
		{
			_act = KeyCheck();
			if (_act(*this,itr.second))
			{
				//_act = HitCheck();
				//if (_act(*this))
				//{

				//}
			}
		}
	}


	//	�����蔻�菈��
	CheckCol();
	//	�d�͂����W�ɉ��Z����
	setPosition(getPosition().x, getPosition().y + _Gravity);
	//	�f�o�b�O�pBox�̍��W�ݒ�
#ifdef _DEBUG
	_box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	_box->setPosition(getPosition());
#endif // _DEBUG

	//	�����̍X�V
	dirUpdate();
	//	�ړ��̍X�V
	moveUpdate();
	//	�A�j���[�V�����̍X�V
	AnimStateUpdate();
}

