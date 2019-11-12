#pragma once
#include "OprtState.h"

//enum INPUT_KEY
//{
//	LEFT,
//	RIGHT,
//	UP,
//	DOWN,
//	INPUT_MAX
//};
//
//using inputMap = std::vector<INPUT_KEY, int>;

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);								//	キャラクターではないオブジェクト用
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara);				//	キャラクター用
	void update();
	UseKey GetPressKey();

private:
	UseKey _pressKey;
	UseKey _releaseKey;
	//inputMap _input;
};

