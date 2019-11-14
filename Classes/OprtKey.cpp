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
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	���ړ�
			_pressKey = UseKey::K_LEFT;

			//chara->SetMovePosX(- speed);
			//chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	�E�ړ�
			_pressKey = UseKey::K_RIGHT;

			//chara->SetMovePosX(speed);
			//chara->SetMoveFlagX(true);
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//if (chara->GetMovePos().y == 0)
			{
				//	�W�����v
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

	//	�L�[�𗣂����u��
	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_releaseKey = UseKey::K_LEFT;
			////	movePosX�����Ɍ������Ă�����0�ɂ���
			//if (chara->GetMovePos().x < 0)
			//{
			//	chara->SetMovePosX(0);
			//	chara->SetMoveFlagX(false);
			//}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_releaseKey = UseKey::K_RIGHT;

			////	movePosX���E�Ɍ������Ă�����0�ɂ���
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


