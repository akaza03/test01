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
	//	押されたキーのチェック
	auto pressKey = _oprtState->GetPressKey();

	//	離されたキーのチェック
	auto releaseKey = _oprtState->GetReleaseKey();

	for (auto &itr : _charaList)
	{
		if (_state == itr.second.anim)
		{
			////	押されたキーのチェック
			//auto checkKey = _oprtState->GetPressKey();
			////	そのキーがマップにあるか検索(0なら存在しない)
			//if (itr.second.key.count(checkKey) != 0)
			//{
			//	//	nowもoldもfalseの場合
			//	if (!itr.second.key[checkKey].first)
			//	{
			//		itr.second.key[checkKey].first = true;

			//	}
			//	//	nowが既にtrueだった場合
			//	else if(itr.second.key[checkKey].first)
			//	{
			//		itr.second.key[checkKey].first = false;
			//	}
			//}

			itr.second.key[pressKey].first = true;
			itr.second.key[releaseKey].first = false;

			//	移動
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

			//	当たり判定
			if (HitCheck()(*this, itr.second))
			{
				//itr.
				//itr.second.speed = 0;
			}

			//	アニメーションの更新
			//if (itr.second.anim != _oldState)
			//{
			//	lpAnimManager.AnimRun(this, itr.second.anim, itr.second.cType);
			//}
			if (_state != _oldState)
			{
				//	次のアニメーションに現在のキー情報を渡す準備
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

				//	キーの初期化
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


//	//	当たり判定処理
	//CheckCol();
//	//	重力を座標に加算する
//	setPosition(getPosition().x, getPosition().y + _Gravity);
//	//	デバッグ用Boxの座標設定
//#ifdef _DEBUG
//	_box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
//	_box->setPosition(getPosition());
//#endif // _DEBUG
//
//	//	向きの更新
//	dirUpdate();
//	//	移動の更新
//	moveUpdate();
//	//	アニメーションの更新
//	AnimStateUpdate();
}

void Player::SetCharaType()
{
	for (auto itr : _charaList)
	{
		itr.second.cType = CharaType::PLAYER;
	}
}

