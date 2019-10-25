#include "OprtTouch.h"


OprtTouch::OprtTouch()
{
	//moveFlag = false;
}


OprtTouch::~OprtTouch()
{
}

cocos2d::EventListener * OprtTouch::moveEv(cocos2d::Sprite *sprite, int speed)
{
	//	シングルタッチ
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	マルチタッチ
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;

		BackOldPos = OldTouchPos;
		BackNowPos = NowTouchPos;

		StartTouchPos = touch->getLocation();
		NowTouchPos = StartTouchPos;

		//	開始位置に目印を作成
		StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(StartTouchPos);
		nowScene->addChild(StartSP);

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [sprite, speed,this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;
		NowTouchPos = touch->getLocation();

		SetMove(touch,sprite,speed);
		return true;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;
		//moveFlag = false;
		return true;
	};
	
	return listener;
}

cocos2d::EventListener * OprtTouch::moveEv(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	//	シングルタッチ
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	マルチタッチ
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;

		BackOldPos = OldTouchPos;
		BackNowPos = NowTouchPos;

		StartTouchPos = touch->getLocation();
		NowTouchPos = StartTouchPos;

		//	開始位置に目印を作成
		StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(StartTouchPos);
		nowScene->addChild(StartSP,0,"touchIcon");

		return true;
	};

	//	スワイプ移動時
	listener->onTouchMoved = [sprite, speed, chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;
		NowTouchPos = touch->getLocation();
		chara->SetState(AnimState::RUN);
		chara->SetMoveFlag(true);

		CharaMove(chara, speed);

		return true;
	};

	listener->onTouchEnded = [chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		nowScene->removeChildByName("touchIcon");
		OldTouchPos = NowTouchPos;
		chara->SetState(AnimState::IDLE);
		chara->SetMoveFlag(false);
		return true;
	};

	return listener; 
}

void OprtTouch::SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int Cspeed)
{
	float _ang;
	_ang = static_cast<float>(atan2(StartTouchPos.y - NowTouchPos.y, StartTouchPos.x - NowTouchPos.x));

	int speed = Cspeed;

	charaPosX = sprite->getPosition().x - cosf(_ang) * speed;
	charaPosY = sprite->getPosition().y - sinf(_ang) * speed;

	//	移動量が0でなければ保存
	if (OldTouchPos.x != NowTouchPos.x)
	{
		BackOldPos.x = OldTouchPos.x;
		BackNowPos.x = NowTouchPos.x;
	}

	if (OldTouchPos.y != NowTouchPos.y)
	{
		BackOldPos.y = OldTouchPos.y;
		BackNowPos.y = NowTouchPos.y;
	}
}

void OprtTouch::CharaMove(Character *chara, int speed)
{
	//if (moveFlag)
	{
		float _ang = 0;
		//	スワイプ中に止まっても移動を続けるように

		_ang = static_cast<float>(atan2(StartTouchPos.y - NowTouchPos.y, StartTouchPos.x - NowTouchPos.x));

		charaPosX = chara->getPosition().x - cosf(_ang) * speed;
		charaPosY = chara->getPosition().y - sinf(_ang) * speed;

		chara->SetMovePosX(-cosf(_ang) * speed);
		chara->SetMovePosY(-sinf(_ang) * speed);

		if (chara->getPosition().x < charaPosX)
		{
			chara->SetDir(DIR::RIGHT);
		}
		if (chara->getPosition().x > charaPosX)
		{
			chara->SetDir(DIR::LEFT);
		}
	}
}

void OprtTouch::SetScene(cocos2d::Scene * scene)
{
	nowScene = scene;
}
