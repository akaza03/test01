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
	ENEMY,
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
	void CheckCol();																//	�Փ˔���p(update�ŌĂяo��)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	����������W�̃^�C����Ԃ�

	void moveUpdate();																//	�ړ��̍X�V
	void dirUpdate();																//	�����̍X�V

	Sprite *_box;																	//	�����蔻��p��BOX
	float _Gravity;																	//	�d��
	cocos2d::Vec2 _oldPos;															//	1�t���[���O�̍��W
	OprtState *_oprtState;															//	���쐧��
	AnimState _state;																//	���݂̃A�j���[�V����
	AnimState _oldState;															//	1�t���[���O�̃A�j���[�V����

	bool _moveFlagX;																//	�L�����N�^�[��X���W���ړ������ǂ���
	bool _moveFlagY;																//	�L�����N�^�[��Y���W���ړ������ǂ���
	bool _JumpStart;																//	�W�����v�J�n���̃t���O

	cocos2d::Vec2 _movePos;															//	�ړ����Ɍ��݂̍��W�ɉ��Z����
	int _speed;																		//	�ړ��X�s�[�h

	DIR _charaDir;
	DIR _startDir;
	DIR _oldDir;

	
	std::map<spPointer, spPointer> act;												//	�A�N�V�����̊Ǘ��p
};
