#include "OprtTouch.h"


OprtTouch::OprtTouch()
{
	//moveFlag = false;
}


OprtTouch::~OprtTouch()
{
}

cocos2d::EventListener * OprtTouch::oprtInit(cocos2d::Sprite * sprite)
{
	//	�V���O���^�b�`
	auto listener = cocos2d::EventListenerTouchOneByOne::create();

	//	�}���`�^�b�`
	//auto listener = cocos2d::EventListenerTouchAllAtOnce::create();

	listener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		_startTouchPos = touch->getLocation();

		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();

		//	�J�n�ʒu�ɖڈ���쐬
		auto StartSP = cocos2d::Sprite::create("CloseNormal.png");
		StartSP->setPosition(_startTouchPos);
		nowScene->addChild(StartSP,0,"touchIcon");

		return true;
	};

	//	�X���C�v�ړ���
	listener->onTouchMoved = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		checkKey(touch->getLocation());
		return true;
	};

	listener->onTouchEnded = [this](cocos2d::Touch* touch, cocos2d::Event* event)->bool
	{
		auto nowScene = cocos2d::Director::getInstance()->getRunningScene();
		nowScene->removeChildByName("touchIcon");
		for (auto itrKey : UseKey())
		{
			_oprtKeyList[itrKey] = false;
		}
		return true;
	};

	return listener; 
}

void OprtTouch::update()
{
}

void OprtTouch::checkKey(cocos2d::Vec2 touchPos)
{
	auto offset = 30;
	if (touchPos.x < _startTouchPos.x - offset)
	{
		_oprtKeyList[UseKey::K_LEFT] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_LEFT] = false;
	}

	if (touchPos.x > _startTouchPos.x + offset)
	{
		_oprtKeyList[UseKey::K_RIGHT] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_RIGHT] = false;
	}

	if (touchPos.y > _startTouchPos.y + offset)
	{
		_oprtKeyList[UseKey::K_UP] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_UP] = false;
	}

	if (touchPos.y < _startTouchPos.y - offset)
	{
		_oprtKeyList[UseKey::K_DOWN] = true;
	}
	else
	{
		_oprtKeyList[UseKey::K_DOWN] = false;
	}
}

