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
	for (auto &itr : _charaList)
	{
		if (itr.second.nowAnim == itr.second.anim)
		{
			//	�L�[�̃`�F�b�N
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	���̃L�[���o�^����Ă���΃L�[���X�V����
				if (itr.second.key[checkKey.first].second)
				{
					itr.second.key[checkKey.first].first = checkKey.second;
				}
			}

			//	�d�͂����Z����
			float gy = -0.05f;
			_Gravity += gy;

			//	�����蔻��
			HitCheck()(*this, itr.second);

			//	�ړ�����
			itr.second.distance.y = Jump()(*this, itr.second);
			itr.second.distance.x = Move()(*this, itr.second);

			//	�d�͂�0��
			if (itr.second.checkPoint[DIR::DOWN])
			{
				_Gravity = 0;
			}

			//	�A�j���[�V�����̍X�V
			if (itr.second.distance.y != 0)
			{
				itr.second.nowAnim = AnimState::JUMP;
			}
			else if (itr.second.distance.x != 0)
			{
				itr.second.nowAnim = AnimState::RUN;
			}
			else
			{
				itr.second.nowAnim = AnimState::IDLE;
			}

			//	�ړ�
			setPosition(getPosition().x + itr.second.distance.x, getPosition().y + itr.second.distance.y + _Gravity);

			//	�����̍X�V
			auto oldDir = itr.second.dir;
			if (itr.second.distance.x < 0)
			{
				itr.second.dir = DIR::LEFT;
			}
			else if (itr.second.distance.x > 0)
			{
				itr.second.dir = DIR::RIGHT;
			}

			if (oldDir != itr.second.dir)
			{
				if (itr.second.dir == DIR::LEFT)
				{
					setFlippedX(true);
				}
				else if (itr.second.dir == DIR::RIGHT)
				{
					setFlippedX(false);
				}
			}

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	���̃A�j���[�V�����Ɍ��݂̃L�[����n������
				char* nextKeyName = "idle";
				switch (itr.second.nowAnim)
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
				for (auto itrKey : UseKey())
				{
					//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����̃L�[����n��
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					//	���̃A�j���[�V�����̃L�[����������
					itr.second.key[itrKey].first = false;
				}
				//	���̃A�j���[�V�����Ɍ��݂̃A�j���[�V�����ƌ�����n��
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.dir = itr.second.dir;

				lpAnimManager.AnimRun(this, itr.second.nowAnim, itr.second.cType);
			}
		}
	}
}

