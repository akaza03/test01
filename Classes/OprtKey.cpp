#include "OprtKey.h"

OprtKey::OprtKey()
{
}


OprtKey::~OprtKey()
{
}

cocos2d::EventListener * OprtKey::moveEv(cocos2d::Sprite *sprite, int speed)
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

cocos2d::EventListener * OprtKey::moveEv(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	listener->onKeyPressed = [speed, chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		chara->SetMoveFlag(true);

		chara->SetState(AnimState::RUN);
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	���ړ�
			chara->SetMovePosX(- speed);
			chara->SetDir(DIR::LEFT);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	�E�ړ�
			chara->SetMovePosX(speed);
			chara->SetDir(DIR::RIGHT);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//	��ړ�
			chara->SetMovePosY(speed);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			//	���ړ�
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

void OprtKey::CharaMove(Character *chara, int speed)
{
}

void OprtKey::SetScene(cocos2d::Scene * scene)
{
	nowScene = scene;
}

