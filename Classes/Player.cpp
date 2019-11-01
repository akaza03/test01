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
	//	当たり判定処理
	CheckCol();

	//	重力を座標に加算する
	setPosition(getPosition().x, getPosition().y + _Gravity);

	//	デバッグ用Boxの座標設定
#ifdef _DEBUG
	_box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	_box->setPosition(getPosition());
#endif // _DEBUG

	//	方向の更新
	dirUpdate();
	//	移動の更新
	moveUpdate();
	//	アニメーションの更新
	AnimStateUpdate();
}

void Player::SetDBBox(Sprite* sp)
{
#ifdef _DEBUG
	//	当たり判定用の四角描画
	_box = sp;
#endif // _DEBUG
}


void Player::AnimStateUpdate()
{
	//	AnimStateの更新
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

	//	アニメーションの更新
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



