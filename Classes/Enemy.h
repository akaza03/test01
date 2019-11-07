#pragma once
#include "Character.h"

class Enemy :
	public Character
{
public:
	Enemy();
	~Enemy();
	void update(float d);
	void SetCharaType();
	CREATE_FUNC(Enemy);
private:
	void AnimStateUpdate();
};

