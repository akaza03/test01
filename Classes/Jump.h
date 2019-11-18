#pragma once
#include <cocos2d.h>

struct Jump
{
	float operator()(cocos2d::Sprite & sp, struct ActData &act);
};
