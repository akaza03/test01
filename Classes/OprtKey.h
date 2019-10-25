#pragma once
#include "OprtState.h"

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed);
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed, Character *chara);
	void CharaMove(Character *chara, int speed);
	void SetScene(cocos2d::Scene *scene);
};

