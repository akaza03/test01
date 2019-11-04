#pragma once
#include <cocos2d.h>

struct KeyCheck
{
	bool operator()(cocos2d::Sprite & sp, struct CharaID &st);
};
