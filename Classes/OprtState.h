#pragma once
#include "cocos2d.h"
#include "AnimManager.h"
#include "Character.h"

class OprtState
{
public:
	OprtState();
	virtual ~OprtState();
	virtual cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed) = 0;
	virtual cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed, Character *chara) = 0;
	virtual void CharaMove(Character *chara, int speed) = 0;
	virtual void SetScene(cocos2d::Scene *scene) = 0;
protected:
	cocos2d::Scene *nowScene;
};