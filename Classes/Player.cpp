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
	//	押されたキーのチェック
	auto pressKey = _oprtState->GetPressKey();

	//	離されたキーのチェック
	auto releaseKey = _oprtState->GetReleaseKey();

	for (auto &itr : _charaList)
	{
		if (_state == itr.second.anim)
		{
			//	そのキーが登録されていればキーを更新する
			if (itr.second.key[pressKey].second)
			{
				itr.second.key[pressKey].first = true;
			}
			if (itr.second.key[releaseKey].second)
			{
				itr.second.key[releaseKey].first = false;
			}

			//	重力を加算する
			float gy = -0.05f;
			_Gravity += gy;

			//	移動距離
			auto distance = cocos2d::Vec2(0,0);

			//	当たり判定
			HitCheck()(*this, itr.second);
			distance.y = Jump()(*this, itr.second);
			
			if(itr.second.checkPoint[DIR::DOWN])
			{
				_Gravity = 0;
			}

			distance.x = Move()(*this, itr.second);

			//	移動
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

			//	アニメーションの更新
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
					nextKey.key[itrKey].first = itr.second.key[itrKey].first;
					itr.second.key[itrKey].first = false;
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

