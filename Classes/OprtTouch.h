#pragma once
#include "OprtState.h"


class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed);

	//	キャラクター用
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed, Character *chara);
	//	キャラクターの移動用
	void CharaMove(Character *chara, int speed);
	void SetScene(cocos2d::Scene *scene);
private:
	//	移動開始時の準備用
	void SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int speed);

	//	タッチ開始時の座標
	cocos2d::Vec2 StartTouchPos;
	//	現在のタッチ座標
	cocos2d::Vec2 NowTouchPos;
	//	1フレーム前のタッチ座標
	cocos2d::Vec2 OldTouchPos;

	//	NowTouchPos保存用
	cocos2d::Vec2 BackNowPos;
	//	OldTouchPos保存用
	cocos2d::Vec2 BackOldPos;

	float charaPosX;
	float charaPosY;

	bool moveFlag;

	cocos2d::Sprite *StartSP;
};

