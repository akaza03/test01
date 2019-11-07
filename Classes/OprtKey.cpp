#include "OprtKey.h"

OprtKey::OprtKey()
{

}


OprtKey::~OprtKey()
{
}

//	キャラクターではないオブジェクト用
cocos2d::EventListener * OprtKey::oprtInit(cocos2d::Sprite *sprite, int speed)
{
	auto listener = cocos2d::EventListenerKeyboard::create();
	listener->onKeyPressed = [sprite,speed](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{

		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	左移動
			sprite->setPositionX(sprite->getPositionX() - speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	右移動
			sprite->setPositionX(sprite->getPositionX() + speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//	上移動
			sprite->setPositionY(sprite->getPositionY() + speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//	下移動
			sprite->setPositionY(sprite->getPositionY() - speed);
		}
	};
	return listener;
}

//	キャラクター用
cocos2d::EventListener * OprtKey::oprtInit(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	//	キーを押した瞬間
	listener->onKeyPressed = [speed, chara, this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{		
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	左移動
			chara->SetMovePosX(- speed);
			chara->SetMoveFlagX(true);
			
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	右移動
			chara->SetMovePosX(speed);
			chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			if (chara->GetMovePos().y == 0)
			{
				//	ジャンプ
				chara->SetMovePosY(speed);
				chara->SetMoveFlagY(true);
				chara->SetJumpStart(true);
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//chara->SetState(AnimState::DUCK);
		}

		_keyCode = keyCode;
	};

	//	キーを離した瞬間
	listener->onKeyReleased = [speed,chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	movePosXが左に向かっていたら0にする
			if (chara->GetMovePos().x < 0)
			{
				chara->SetMovePosX(0);
				chara->SetMoveFlagX(false);
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	movePosXが右に向かっていたら0にする
			if (chara->GetMovePos().x > 0)
			{
				chara->SetMovePosX(0);
				chara->SetMoveFlagX(false);
			}
		}
	};

	return listener;
}

void OprtKey::update()
{
}

cocos2d::EventKeyboard::KeyCode OprtKey::GetKeyCode()
{
	return _keyCode;
}
