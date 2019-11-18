#include "Player.h"

Player::Player()
{
	_actData.cType = CharaType::PLAYER;

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	//	�����ꂽ�L�[�̃`�F�b�N
	auto pressKey = _oprtState->GetPressKey();

	//	�����ꂽ�L�[�̃`�F�b�N
	auto releaseKey = _oprtState->GetReleaseKey();

	for (auto &itr : _charaList)
	{
		if (_state == itr.second.anim)
		{
			//	���̃L�[���o�^����Ă���΃L�[���X�V����
			if (itr.second.key[pressKey].second)
			{
				itr.second.key[pressKey].first = true;
			}
			if (itr.second.key[releaseKey].second)
			{
				itr.second.key[releaseKey].first = false;
			}

			//	�d�͂����Z����
			float gy = -0.05f;
			_Gravity += gy;

			//	�ړ�����
			auto distance = cocos2d::Vec2(0,0);

			//	�����蔻��
			HitCheck()(*this, itr.second);
			distance.y = Jump()(*this, itr.second);
			
			if(itr.second.checkPoint[DIR::DOWN])
			{
				_Gravity = 0;
			}

			distance.x = Move()(*this, itr.second);

			//	�ړ�
			if (distance.y != 0)
			{
				_state = AnimState::JUMP;
			}
			else if (distance.x != 0)
			{
				_state = AnimState::RUN;
			}
			else
			{
				_state = AnimState::IDLE;
			}

			setPosition(getPosition().x + distance.x, getPosition().y + distance.y + _Gravity);

			//	�A�j���[�V�����̍X�V
			if (_state != _oldState)
			{
				//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
				char* nextKeyName;
				switch (_state)
				{
				case IDLE:
					nextKeyName = "idle";
					break;
				case RUN:
					nextKeyName = "run";
					break;
				case RSHOT:
					nextKeyName = "pShot";
					break;
				case SHOTUP:
					nextKeyName = "shotUp";
					break;
				case STAND:
					nextKeyName = "stand";
					break;
				case JUMP:
					nextKeyName = "jump";
					break;
				case CLING:
					nextKeyName = "cling";
					break;
				case DUCK:
					nextKeyName = "duck";
					break;
				case HURT:
					nextKeyName = "hurt";
					break;
				case STATE_MAX:
					break;
				default:
					break;
				}
				auto &nextKey = _charaList[nextKeyName];

				//	�L�[�̏�����
				for (auto itrKey:UseKey())
				{
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					itr.second.key[itrKey].first = false;
				}
				lpAnimManager.AnimRun(this, _state, itr.second.cType);
			}
			_oldState = _state;
		}
	}
	_oprtState->update();


//	//	�����蔻�菈��
	//CheckCol();
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

