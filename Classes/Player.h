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
	//	Õ“Ë”»’è—p(update‚ÅŒÄ‚Ño‚·)
	void CheckCol();
};
