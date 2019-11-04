#pragma once
#include <functional>
#include "ActSet.h"
#include "AnimManager.h"
#include "OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct CharaID&)>;

//	�L�����N�^�[�̏��p
struct CharaID
{
	cocos2d::Vec2 speed;													//	�ړ��X�s�[�h
	cocos2d::EventKeyboard::KeyCode key;									//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;															//	���݂̃A�j���[�V����
	cocos2d::Point checkPoint;												//	�����蔻��p
	CharaType cType;														//	�L�����N�^�[�̃^�C�v
	//	���ɌĂԊ֐�
};

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

	CharaType GetCharaType();														//	�L�����̃^�C�v��Get

	void SetDBBox(Sprite* sp);														//	�f�o�b�O���̓����蔻��pBox��Set

protected:
	void CheckCol();																//	�Փ˔���p(update�ŌĂяo��)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	����������W�̃^�C����Ԃ�

	void dirUpdate();																//	�����̍X�V
	void moveUpdate();																//	�ړ��̍X�V
	void AnimStateUpdate();															//	�A�j���[�V�����̍X�V

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

	DIR _charaDir;																	//	�L�����N�^�[�̌���
	DIR _startDir;																	//	�Q�[���J�n���̌���
	DIR _oldDir;																	//	1�t���[���O�̌���

	CharaType _cType;																//	�L�����N�^�[�̃^�C�v



	CharaID _charaID;														//	�L�����N�^�[�̏��p
	std::map<const char *,CharaID> _charaList;								//	�L�����N�^�[�̏��p���X�g
	std::list<cocos2d::EventKeyboard::KeyCode> _keyList;					//	�L�[�p�̃��X�g

	std::list<actionPoint> _actList;										//	�A�N�V�����̊Ǘ��p

	actionPoint _act;

	//bool(*_act)(cocos2d::Sprite&);
};
