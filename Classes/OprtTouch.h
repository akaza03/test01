#pragma once
#include "OprtState.h"

class OprtTouch
	:public OprtState
{
public:
	OprtTouch();
	~OprtTouch();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);						//	�L�����N�^�[�ł͂Ȃ��I�u�W�F�N�g�p
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara);		//	�L�����N�^�[�p

private:
	void SetMove(cocos2d::Touch* touch, cocos2d::Sprite *sprite, int speed);					//	�ړ��J�n���̏����p

	void CharaMove(Character *chara, int speed);												//	�L�����N�^�[�̈ړ��p

	cocos2d::Vec2 StartTouchPos;																//	�^�b�`�J�n���̍��W
	cocos2d::Vec2 NowTouchPos;																	//	���݂̃^�b�`���W
	cocos2d::Vec2 OldTouchPos;																	//	1�t���[���O�̃^�b�`���W
	cocos2d::Vec2 BackNowPos;																	//	NowTouchPos�ۑ��p
	cocos2d::Vec2 BackOldPos;																	//	OldTouchPos�ۑ��p

	float charaPosX;
	float charaPosY;

	bool moveFlag;
};

