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
	void CheckCol();																//	衝突判定用(updateで呼び出す)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	代入した座標のタイルを返す
};
