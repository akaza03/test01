#include "HitCheck.h"

//bool HitCheck::operator()(cocos2d::Sprite & sp/*,構造体、mapとかlistとか*/)
//{
//	auto pos = &sp.getPosition();
//	return false;
//}

bool HitCheck::operator()(cocos2d::Sprite & sp)
{
	//auto pos = sp->getPosition();
	return false;
}

