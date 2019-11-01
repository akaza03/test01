#include "Player.h"

Player::Player()
{
	_state = AnimState::IDLE;
	_oldState = AnimState::STATE_MAX;
	_movePos = cocos2d::Vec2(0, 0);

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
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

void Player::SetDBBox(Sprite* sp)
{
#ifdef _DEBUG
	//	�����蔻��p�̎l�p�`��
	_box = sp;
#endif // _DEBUG
}


void Player::AnimStateUpdate()
{
	//	AnimState�̍X�V
	if (_moveFlagY)
	{
		_state = AnimState::JUMP;
	}
	else if (_moveFlagX)
	{
		_state = AnimState::RUN;
	}
	else
	{
		_state = AnimState::IDLE;
	}

	//	�A�j���[�V�����̍X�V
	if (_state != _oldState)
	{
		switch (_state)
		{
		case AnimState::IDLE:
			lpAnimManager.AnimRun(this, "p_idle");
			break;
		case AnimState::RUN:
			lpAnimManager.AnimRun(this, "p_run");
			break;
		case AnimState::SHOTUP:
			lpAnimManager.AnimRun(this, "p_shotUp");
			break;
		case AnimState::STAND:
			lpAnimManager.AnimRun(this, "p_stand");
			break;
		case AnimState::JUMP:
			lpAnimManager.AnimRun(this, "p_jump");
			break;
		case AnimState::CLING:
			lpAnimManager.AnimRun(this, "p_cling");
			break;
		case AnimState::DUCK:
			lpAnimManager.AnimRun(this, "p_duck");
			break;
		case AnimState::HURT:
			lpAnimManager.AnimRun(this, "p_hurt");
			break;
		case AnimState::STATE_MAX:
			break;
		default:
			break;
		}
	}
	_oldState = _state;
}



