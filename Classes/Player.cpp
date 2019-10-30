#include "Player.h"

Player::Player()
{
	//Sprite::create("image/Sprites/player/player-idle/player-idle-1.png");

	state = AnimState::IDLE;
	oldState = AnimState::STATE_MAX;
	movePos = cocos2d::Vec2(0, 0);

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	CheckCol();

	moveUpdate();

	//	プレイヤーの向きの更新
	if (charaDir != OldDir)
	{
		if (charaDir != startDir)
		{
			setFlippedX(true);
		}
		else
		{
			setFlippedX(false);
		}
		
	}
	OldDir = charaDir;

	AnimStateUpdate();
}

void Player::SetDBBox(Sprite* sp)
{
#ifdef _DEBUG
	//	当たり判定用の四角描画
	box = sp;
#endif // _DEBUG
}

void Player::moveUpdate()
{
	JumpStart = false;
	//	移動
	if (moveFlagX)
	{
		setPosition(getPosition().x + movePos.x,getPosition().y);
	}
	if (moveFlagY)
	{
		setPosition(getPosition().x, getPosition().y + movePos.y);
	}

	//	アニメーションの更新
	if (moveFlagY)
	{
		state = AnimState::JUMP;
	}
	else if (moveFlagX)
	{
		state = AnimState::RUN;
	}
	else
	{
		state = AnimState::IDLE;
	}
}

void Player::AnimStateUpdate()
{
	//	アニメーションの更新
	if (state != oldState)
	{
		switch (state)
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
	oldState = state;
}



