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
	DIR_MAX
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass,DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene);

	void MoveAction();
	//	�A�j���[�V�����̃X�e�[�g��GetSet
	AnimState GetState();
	void SetState(AnimState st);
	//	������GetSet
	DIR GetDir();
	void SetDir(DIR dir);
	//	�X�s�[�h��GetSet
	void SetSpeed(int sp);
	int GetSpeed();

	void SetMoveFlag(bool flag);
	//	�ړ�������GetSet
	void SetMovePosX(float pos);
	void SetMovePosY(float pos);

protected:
	float Gy;								//	�d�͗p

	OprtState *_oprtState;

	AnimState state;
	AnimState oldState;
	int speed;
	bool moveFlag;
	cocos2d::Vec2 movePos;					//	�w�𗣂��܂ňړ����邽�߂̈ړ�����
	cocos2d::Vec2 colMovePos;				//	�����蔻���t�^�����ŏI�I��movePos

	DIR charaDir;
	DIR startDir;
	DIR OldDir;
};

