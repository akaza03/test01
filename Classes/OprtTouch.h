#pragma once
#include "OprtState.h"

class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);						//	キャラクターではないオブジェクト用
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara);		//	キャラクター用

private:
	void SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int speed);					//	移動開始時の準備用

	void CharaMove(Character *chara, int speed);												//	キャラクターの移動用

	cocos2d::Vec2 StartTouchPos;																//	タッチ開始時の座標
	cocos2d::Vec2 NowTouchPos;																	//	現在のタッチ座標
	cocos2d::Vec2 OldTouchPos;																	//	1フレーム前のタッチ座標
	cocos2d::Vec2 BackNowPos;																	//	NowTouchPos保存用
	cocos2d::Vec2 BackOldPos;																	//	OldTouchPos保存用

	float charaPosX;
	float charaPosY;

	bool moveFlag;
};

