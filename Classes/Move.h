#pragma once
#include <cocos2d.h>

struct Move
{
	float operator()(cocos2d::Sprite & sp, struct ActData &act);
};

