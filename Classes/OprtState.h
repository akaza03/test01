#pragma once
#include "cocos2d.h"
#include "AnimManager.h"

class Character;

class OprtState
{
public:
	OprtState();
	virtual ~OprtState();
	virtual cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed) = 0;							//	�L�����N�^�[�ł͂Ȃ��I�u�W�F�N�g�p
	virtual cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara) = 0;			//	�L�����N�^�[�p												
protected:

};