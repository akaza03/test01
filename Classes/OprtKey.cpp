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
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	左移動
			_pressKey = UseKey::K_LEFT;

			//chara->SetMovePosX(- speed);
			//chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	右移動
			_pressKey = UseKey::K_RIGHT;

			//chara->SetMovePosX(speed);
			//chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//if (chara->GetMovePos().y == 0)
			{
				//	ジャンプ
				_pressKey = UseKey::K_UP;

				//chara->SetMovePosY(speed);
				//chara->SetMoveFlagY(true);
				//chara->SetJumpStart(true);
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_pressKey = UseKey::K_DOWN;
			//chara->SetState(AnimState::DUCK);
		}
	};

	//	キーを離した瞬間
	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_releaseKey = UseKey::K_LEFT;
			////	movePosXが左に向かっていたら0にする
			//if (chara->GetMovePos().x < 0)
			//{
			//	chara->SetMovePosX(0);
			//	chara->SetMoveFlagX(false);
			//}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_releaseKey = UseKey::K_RIGHT;

			////	movePosXが右に向かっていたら0にする
			//if (chara->GetMovePos().x > 0)
			//{
			//	chara->SetMovePosX(0);
			//	chara->SetMoveFlagX(false);
			//}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			_releaseKey = UseKey::K_UP;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_releaseKey = UseKey::K_DOWN;
		}
	};

	return listener;
}

void OprtKey::update()
{
	_pressKey = UseKey::K_NON;
	_releaseKey = UseKey::K_NON;
}

UseKey OprtKey::GetPressKey()
{
	return _pressKey;
}

UseKey OprtKey::GetReleaseKey()
{
	return _releaseKey;
}


