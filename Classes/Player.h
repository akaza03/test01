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
	//	�Փ˔���p(update�ŌĂяo��)
	void CheckCol();
};
