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
		//	キーのチェック
		auto checkKey = _oprtState->GetKeyCode();

		//	そのキーがマップにあるか検索(0なら存在しない)
		if (itr.second.key.count(checkKey) != 0)
		{

			//	あった場合はnowをtrueに
			itr.second.key[checkKey].first = true;

			//	now != old
			if (itr.second.key[checkKey].first != itr.second.key[checkKey].second)
			{

			}
		}

		//	当たり判定
		if (HitCheck()(*this, itr.second))
		{
			//itr.
			//itr.second.speed = 0;
		}

		//	アニメーションの更新
		if (itr.second.anim != _oldState)
		{
			lpAnimManager.AnimRun(this, itr.second.anim, itr.second.cType);
		}

		//	キーの更新
		for (auto keyItr : itr.second.key)
		{
			//	old = now
			keyItr.second.second = keyItr.second.first;
		}
	}



//	//	当たり判定処理
//	CheckCol();
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

