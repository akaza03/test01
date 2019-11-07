#include "OprtKey.h"

OprtKey::OprtKey()
{

}


OprtKey::~OprtKey()
{
}

//	�L�����N�^�[�ł͂Ȃ��I�u�W�F�N�g�p
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

//	�L�����N�^�[�p
cocos2d::EventListener * OprtKey::oprtInit(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	//	�L�[���������u��
	listener->onKeyPressed = [speed, chara, this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{		
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	���ړ�
			chara->SetMovePosX(- speed);
			chara->SetMoveFlagX(true);
			
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	�E�ړ�
			chara->SetMovePosX(speed);
			chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			if (chara->GetMovePos().y == 0)
			{
				//	�W�����v
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

	//	�L�[�𗣂����u��
	listener->onKeyReleased = [speed,chara](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	movePosX�����Ɍ������Ă�����0�ɂ���
			if (chara->GetMovePos().x < 0)
			{
				chara->SetMovePosX(0);
				chara->SetMoveFlagX(false);
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	movePosX���E�Ɍ������Ă�����0�ɂ���
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
