#include "OprtKey.h"

OprtKey::OprtKey()
{

}


OprtKey::~OprtKey()
{
}


cocos2d::EventListener * OprtKey::oprtInit(cocos2d::Sprite * sprite)
{
	auto listener = cocos2d::EventListenerKeyboard::create();

	//	キーを押した瞬間
	listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			//	左移動
			_oprtKeyList[UseKey::K_LEFT] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			//	右移動
			_oprtKeyList[UseKey::K_RIGHT] = true;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			//if (chara->GetMovePos().y == 0)
			{
				//	ジャンプ
				_oprtKeyList[UseKey::K_UP] = true;
			}
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_oprtKeyList[UseKey::K_DOWN] = true;
		}
	};

	//	キーを離した瞬間
	listener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* keyEvent)
	{
		if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			_oprtKeyList[UseKey::K_LEFT] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			_oprtKeyList[UseKey::K_RIGHT] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			_oprtKeyList[UseKey::K_UP] = false;
		}
		else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			_oprtKeyList[UseKey::K_DOWN] = false;
		}
	};

	return listener;
}

void OprtKey::update()
{
}
