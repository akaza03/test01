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
	//	�V���O���^�b�`
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	�}���`�^�b�`
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;

		BackOldPos = OldTouchPos;
		BackNowPos = NowTouchPos;

		StartTouchPos = touch->getLocation();
		NowTouchPos = StartTouchPos;

		return true;
	};

	//	�X���C�v�ړ���
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

cocos2d::EventListener * OprtTouch::oprtInit(cocos2d::Sprite * sprite, int speed, Character *chara)
{
	//	�V���O���^�b�`
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	�}���`�^�b�`
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		OldTouchPos = NowTouchPos;

		BackOldPos = OldTouchPos;
		BackNowPos = NowTouchPos;

		StartTouchPos = touch->getLocation();
		NowTouchPos = StartTouchPos;

		//	�J�n�ʒu�ɖڈ���쐬
		auto StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(StartTouchPos);
		nowScene->addChild(StartSP,0,"touchIcon");

		return true;
	};

	//	�X���C�v�ړ���
	listener->onTouchMoved = [sprite, speed, chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		OldTouchPos = NowTouchPos;
		NowTouchPos = touch->getLocation();
		chara->SetState(AnimState::RUN);
		chara->SetMoveFlagX(true);

		CharaMove(chara, speed);

		return true;
	};

	listener->onTouchEnded = [chara, this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->removeChildByName("touchIcon");
		OldTouchPos = NowTouchPos;
		chara->SetState(AnimState::IDLE);
		chara->SetMoveFlagX(false);
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

	//	�ړ��ʂ�0�łȂ���Εۑ�
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
	float _ang = 0;
	//	�X���C�v���Ɏ~�܂��Ă��ړ��𑱂���悤��

	_ang = static_cast<float>(atan2(StartTouchPos.y - NowTouchPos.y, StartTouchPos.x - NowTouchPos.x));

	charaPosX = - cosf(_ang) * speed;
	charaPosY = - sinf(_ang) * speed;

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

	//if (chara->getPosition().x < charaPosX)
	//{
	//	chara->SetDir(DIR::RIGHT);
	//}
	//if (chara->getPosition().x > charaPosX)
	//{
	//	chara->SetDir(DIR::LEFT);
	//}
}

