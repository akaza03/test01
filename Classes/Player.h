#pragma once
#include "Character.h"

class Player
	:public Character
{
public:
	Player();
	~Player();
	void update(float d);
	CREATE_FUNC(Player);

	void SetDBBox(Sprite* sp);
private:
	Sprite *box;
	void CheckCol();																//	�Փ˔���p(update�ŌĂяo��)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	����������W�̃^�C����Ԃ�
};
