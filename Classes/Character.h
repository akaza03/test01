#pragma once
#include <functional>
#include "ActSet.h"
#include "AnimManager.h"
#include "UseKey.h"
#include "OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;
using keyList = std::map<UseKey, std::pair<bool, bool>>;							//	�L�[�p�̃��X�g(������Ă��邩�̔���,�o�^����Ă��邩�̔���)
using hitList = std::map<DIR, bool>;												//	�����蔻��p���X�g

//	�L�����N�^�[�̏��p
struct ActData
{
	int speed;																		//	�ړ��X�s�[�h
	keyList key;																	//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;																	//	�Đ�����A�j���[�V����
	hitList checkPoint;																//	�����蔻��p
	//cocos2d::Point checkPoint;
	CharaType cType;																//	�L�����N�^�[�̃^�C�v
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

	void SetDBBox(Sprite* sp);														//	�f�o�b�O���̓����蔻��pBox��Set

private:
	void InitActData(int speed);													//	ActData�̏�����

protected:
	Sprite *_box;																	//	�����蔻��p��BOX
	float _Gravity;																	//	�d��
	OprtState *_oprtState;															//	���쐧��
	AnimState _state;																//	���݂̃A�j���[�V����
	AnimState _oldState;															//	1�t���[���O�̃A�j���[�V����
	ActData _actData;																//	�L�����N�^�[�̏��p
	std::map<const char *,ActData> _charaList;										//	�L�����N�^�[�̏��p���X�g

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;							//	�L�[�p�̃��X�g

	//std::list<actionPoint> _actList;												//	�A�N�V�����̊Ǘ��p

	//bool(*_act)(cocos2d::Sprite&, ActData &);										//	�֐��|�C���^
};
