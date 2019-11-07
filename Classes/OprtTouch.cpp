#include "OprtTouch.h"


OprtTouch::OprtTouch()
{
	//moveFlag = false;
}


OprtTouch::~OprtTouch()
{
}

cocos2d::EventListener * OprtTouch::oprtInit(cocos2d::Sprite *sprite, int speed)
{
	//	シングルタッチ
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	マルチタッチ
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_oldTouchPos = _nowTouchPos;

		_backOldPos = _oldTouchPos;
		_backNowPos = _nowTouchPos;

		_startTouchPos = touch->getLocation();
		_nowTouchPos = _startTouchPos;

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [sprite, speed,this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_oldTouchPos = _nowTouchPos;
		_nowTouchPos = touch->getLocation();

		SetMove(touch,sprite,speed);
		return true;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_oldTouchPos = _nowTouchPos;
		//moveFlag = false;
		return true;
	};
	
	return listener;
}

cocos2d::EventListener * OprtTouch::oprtInit(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	//	シングルタッチ
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	マルチタッチ
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		_oldTouchPos = _nowTouchPos;

		_backOldPos = _oldTouchPos;
		_backNowPos = _nowTouchPos;

		_startTouchPos = touch->getLocation();
		_nowTouchPos = _startTouchPos;

		//	開始位置に目印を作成
		auto StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(_startTouchPos);
		nowScene->addChild(StartSP,0,"touchIcon");

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [sprite, speed, chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_oldTouchPos = _nowTouchPos;
		_nowTouchPos = touch->getLocation();
		chara->SetState(AnimState::RUN);
		chara->SetMoveFlagX(true);

		CharaMove(chara, speed);

		return true;
	};

	listener->onTouchEnded = [chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->removeChildByName("touchIcon");
		_oldTouchPos = _nowTouchPos;
		chara->SetState(AnimState::IDLE);
		chara->SetMoveFlagX(false);
		return true;
	};

	return listener; 
}

void OprtTouch::update()
{
}

cocos2d::EventKeyboard::KeyCode OprtTouch::GetKeyCode()
{
	return cocos2d::EventKeyboard::KeyCode();
}

void OprtTouch::SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int Cspeed)
{
	float _ang;
	_ang = static_cast<float>(atan2(_startTouchPos.y - _nowTouchPos.y, _startTouchPos.x - _nowTouchPos.x));

	int speed = Cspeed;

	auto charaPosX = sprite->getPosition().x - cosf(_ang) * speed;
	auto charaPosY = sprite->getPosition().y - sinf(_ang) * speed;

	//	移動量が0でなければ保存
	if (_oldTouchPos.x != _nowTouchPos.x)
	{
		_backOldPos.x = _oldTouchPos.x;
		_backNowPos.x = _nowTouchPos.x;
	}

	if (_oldTouchPos.y != _nowTouchPos.y)
	{
		_backOldPos.y = _oldTouchPos.y;
		_backNowPos.y = _nowTouchPos.y;
	}
}

void OprtTouch::CharaMove(Character *chara, int speed)
{
	float _ang = 0;

	//	スワイプ中に止まっても移動を続けるように
	_ang = static_cast<float>(atan2(_startTouchPos.y - _nowTouchPos.y, _startTouchPos.x - _nowTouchPos.x));

	auto charaPosX = - cosf(_ang) * speed;
	auto charaPosY = - sinf(_ang) * speed;

	chara->SetMovePosX(charaPosX);
	if (charaPosY > 0)
	{
		chara->SetMoveFlagY(true);
		chara->SetJumpStart(true);
		chara->SetMovePosY(charaPosY);
	}
	else
	{
		chara->SetMovePosY(0);
	}

	if (charaPosX > 0)
	{
		chara->SetDir(DIR::RIGHT);
	}
	if (charaPosX < 0)
	{
		chara->SetDir(DIR::LEFT);
	}
}

