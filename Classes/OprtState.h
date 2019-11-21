#pragma once
#include "cocos2d.h"
#include "AnimManager.h"

//	�����ꂽ���ǂ����̔���pList
using OprtKeyList = std::map<UseKey, bool>;

class Character;

class OprtState
{
public:
	OprtState();
	virtual ~OprtState();
	virtual cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite) = 0;
	virtual void update() = 0;
	OprtKeyList GetKeyList();
protected:
	OprtKeyList _oprtKeyList;					
};