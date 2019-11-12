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
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);								//	�L�����N�^�[�ł͂Ȃ��I�u�W�F�N�g�p
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara);				//	�L�����N�^�[�p
	void update();
	UseKey GetPressKey();

private:
	UseKey _pressKey;
	UseKey _releaseKey;
	//inputMap _input;
};

