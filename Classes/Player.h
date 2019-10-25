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
	//	衝突判定用(updateで呼び出す)
	void CheckCol();
};
