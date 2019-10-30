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
			//	���ړ�
			sprite->setPositionX(sprite->getPositionX() - speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	�E�ړ�
			sprite->setPositionX(sprite->getPositionX() + speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//	��ړ�
			sprite->setPositionY(sprite->getPositionY() + speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//	���ړ�
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
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	���ړ�
			chara->SetMovePosX(- speed);
			chara->SetDir(DIR::LEFT);
			chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	�E�ړ�
			chara->SetMovePosX(speed);
			chara->SetDir(DIR::RIGHT);
			chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			if (!chara->GetMoveFlagY())
			{
				//	�W�����v
				chara->SetMovePosY(speed);
				chara->SetMoveFlagY(true);
				chara->SetJumpStart(true);
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			chara->SetState(AnimState::DUCK);

			//	���ړ�
			//chara->SetMovePosY(- speed);
		}
	};

	listener->onKeyReleased = [speed,chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			if (chara->GetMovePos().x < 0)
			{
				chara->SetMovePosX(0);
			}
			chara->SetMoveFlagX(false);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			if (chara->GetMovePos().x > 0)
			{
				chara->SetMovePosX(0);
			}
			chara->SetMoveFlagX(false);
		}
	};

	return listener;
}
