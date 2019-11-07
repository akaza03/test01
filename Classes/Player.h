#pragma once
#include "Character.h"

class Player
	:public Character
{
public:
	Player();
	~Player();
	void update(float d);
	void SetCharaType();
	CREATE_FUNC(Player);
};
