#pragma once
#include "OprtState.h"


class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed);

	//	�L�����N�^�[�p
	cocos2d::EventListener* moveEv(cocos2d::Sprite *sprite, int speed, Character *chara);
	//	�L�����N�^�[�̈ړ��p
	void CharaMove(Character *chara, int speed);
	void SetScene(cocos2d::Scene *scene);
private:
	//	�ړ��J�n���̏����p
	void SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int speed);

	//	�^�b�`�J�n���̍��W
	cocos2d::Vec2 StartTouchPos;
	//	���݂̃^�b�`���W
	cocos2d::Vec2 NowTouchPos;
	//	1�t���[���O�̃^�b�`���W
	cocos2d::Vec2 OldTouchPos;

	//	NowTouchPos�ۑ��p
	cocos2d::Vec2 BackNowPos;
	//	OldTouchPos�ۑ��p
	cocos2d::Vec2 BackOldPos;

	float charaPosX;
	float charaPosY;

	bool moveFlag;

	cocos2d::Sprite *StartSP;
};

