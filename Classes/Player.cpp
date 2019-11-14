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
	//	�����ꂽ�L�[�̃`�F�b�N
	auto pressKey = _oprtState->GetPressKey();

	//	�����ꂽ�L�[�̃`�F�b�N
	auto releaseKey = _oprtState->GetReleaseKey();

	for (auto &itr : _charaList)
	{
		if (_state == itr.second.anim)
		{
			////	�����ꂽ�L�[�̃`�F�b�N
			//auto checkKey = _oprtState->GetPressKey();
			////	���̃L�[���}�b�v�ɂ��邩����(0�Ȃ瑶�݂��Ȃ�)
			//if (itr.second.key.count(checkKey) != 0)
			//{
			//	//	now��old��false�̏ꍇ
			//	if (!itr.second.key[checkKey].first)
			//	{
			//		itr.second.key[checkKey].first = true;

			//	}
			//	//	now������true�������ꍇ
			//	else if(itr.second.key[checkKey].first)
			//	{
			//		itr.second.key[checkKey].first = false;
			//	}
			//}

			itr.second.key[pressKey].first = true;
			itr.second.key[releaseKey].first = false;

			//	�ړ�
			if (Jump()(*this, itr.second))
			{
				_state = AnimState::JUMP;
			}
			if (Move()(*this, itr.second))
			{
				_state = AnimState::RUN;
			}
			else
			{
				_state = AnimState::IDLE;
			}

			//	�����蔻��
			if (HitCheck()(*this, itr.second))
			{
				//itr.
				//itr.second.speed = 0;
			}

			//	�A�j���[�V�����̍X�V
			//if (itr.second.anim != _oldState)
			//{
			//	lpAnimManager.AnimRun(this, itr.second.anim, itr.second.cType);
			//}
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
					nextKey.key[itrKey] = itr.second.key[itrKey];
					itr.second.key[itrKey] = std::make_pair(false, false);
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

void Player::SetCharaType()
{
	for (auto itr : _charaList)
	{
		itr.second.cType = CharaType::PLAYER;
	}
}

