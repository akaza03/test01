#pragma once
#include "cocos2d.h"
#include "AnimManager.h"
#include "OprtState.h"

class OprtState;

//	�A�j���[�V�����̃^�C�v
enum AnimState
{
	IDLE,
	RUN,
	RSHOT,
	SHOTUP,
	STAND,
	JUMP,
	CLING,
	DUCK,
	HURT,
	STATE_MAX
};

//	�L�����N�^�[�̃^�C�v
enum CharaType
{
	PLAYER,
	ENEMY1,
	CHARA_MAX
};

//	����
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DIR_MAX
};

using spPointer = bool (*)(cocos2d::Sprite);


class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass,DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene);

	void MoveAction();
	
	AnimState GetState();															//	�A�j���[�V�����̃X�e�[�g��GetSet
	void SetState(AnimState st);
	
	DIR GetDir();																	//	�L�����N�^�[�̌�����GetSet
	void SetDir(DIR dir);
	
	int GetSpeed();																	//	�X�s�[�h��GetSet
	void SetSpeed(int sp);

	bool GetMoveFlagX();															//	X���W���ړ������ǂ�����GetSet
	void SetMoveFlagX(bool flag);

	bool GetMoveFlagY();															//	Y���W���ړ������ǂ�����GetSet
	void SetMoveFlagY(bool flag);

	cocos2d::Vec2 GetMovePos();														//	�ړ�������GetSet
	void SetMovePosX(float pos);
	void SetMovePosY(float pos);

	void SetJumpStart(bool flag);													//	�W�����v�J�n����Set

protected:
	Sprite *box;
	void CheckCol();																//	�Փ˔���p(update�ŌĂяo��)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	����������W�̃^�C����Ԃ�

	float Gy;																		//	�d�͗p

	OprtState *_oprtState;

	AnimState state;
	AnimState oldState;
	int speed;
	bool moveFlagX;																	//	�L�����N�^�[��X���W���ړ������ǂ���
	bool moveFlagY;																	//	�L�����N�^�[��Y���W���ړ������ǂ���
	bool JumpStart;																	//	�W�����v�J�n���̃t���O
	cocos2d::Vec2 movePos;															//	�w�𗣂��܂ňړ����邽�߂̈ړ�����

	DIR charaDir;
	DIR startDir;
	DIR OldDir;

	
	std::map<spPointer, spPointer> act;												//	�A�N�V�����̊Ǘ��p
};

