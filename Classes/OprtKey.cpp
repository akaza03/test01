#include "OprtKey.h"

OprtKey::OprtKey()
{
}


OprtKey::~OprtKey()
{
}

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

cocos2d::EventListener * OprtKey::oprtInit(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = [speed, chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		chara->SetMoveFlag(true);

		chara->SetState(AnimState::RUN);
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	左移動
			chara->SetMovePosX(- speed);
			chara->SetDir(DIR::LEFT);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	右移動
			chara->SetMovePosX(speed);
			chara->SetDir(DIR::RIGHT);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//	上移動
			chara->SetMovePosY(speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//	下移動
			chara->SetMovePosY(- speed);
		}
	};

	listener->onKeyReleased = [chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		chara->SetMoveFlag(false);
		chara->SetState(AnimState::IDLE);
	};

	return listener;
}
