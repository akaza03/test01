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
			//	キーのチェック
			for (auto checkKey : _oprtState->GetKeyList())
			{
				//	そのキーが登録されていればキーを更新する
				if (itr.second.key[checkKey.first].second)
				{
					itr.second.key[checkKey.first].first = checkKey.second;
				}
			}

			//	モジュールを使用したアクション処理
			ActModule()(*this, itr.second);

			if (itr.second.nowAnim != itr.second.anim)
			{
				//	次のアニメーションに現在のキー情報を渡す準備
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

				//	キーの初期化
				for (auto itrKey : UseKey())
				{
					//	次のアニメーションに現在のアニメーションのキー情報を渡す
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					//	今のアニメーションのキー情報を初期化
					itr.second.key[itrKey].first = false;
				}
				//	次のアニメーションに現在のアニメーションと向きを渡す
				nextKey.nowAnim = itr.second.nowAnim;
				nextKey.dir = itr.second.dir;
				nextKey.Gravity = itr.second.Gravity;
				nextKey.jumpFlag = itr.second.jumpFlag;
				nextKey.jumpCnt = itr.second.jumpCnt;

				lpAnimManager.AnimRun(this, itr.second.nowAnim, itr.second.cType);
			}
		}
	}
}

