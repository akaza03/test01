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


	//	当たり判定処理
	CheckCol();
	//	重力を座標に加算する
	setPosition(getPosition().x, getPosition().y + _Gravity);
	//	デバッグ用Boxの座標設定
#ifdef _DEBUG
	_box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	_box->setPosition(getPosition());
#endif // _DEBUG

	//	向きの更新
	dirUpdate();
	//	移動の更新
	moveUpdate();
	//	アニメーションの更新
	AnimStateUpdate();
}

