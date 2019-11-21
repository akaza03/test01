#pragma once
#include <functional>
#include "ActSet.h"
#include "AnimManager.h"
#include "UseKey.h"
#include "ActModule.h"
#include "OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;
using keyList = std::map<UseKey, std::pair<bool, bool>>;					//	�L�[�p�̃��X�g(������Ă��邩�̔���,�o�^����Ă��邩�̔���)
using hitList = std::map<DIR, bool>;										//	�����蔻��p���X�g

//	�L�����N�^�[�̏��p
struct ActData
{
	cocos2d::Vec2 speed;													//	�ړ��X�s�[�h(����,�W�����v)
	float Gravity = 0;														//	�d��
	keyList key;															//	�ǂ̃L�[���������珈������̂�(List)
	AnimState anim;															//	���g�̃A�j���[�V����
	AnimState nowAnim = AnimState::IDLE;									//	���݂̃A�j���[�V����
	DIR dir = DIR::RIGHT;													//	���݂̌���
	hitList checkPoint;														//	�����蔻��p
	cocos2d::Vec2 distance = { 0,0 };										//	�ړ�����
	bool skyflag = false;													//	�󒆂ɂ��邩�ǂ����̃t���O
	CharaType cType;														//	�L�����N�^�[�̃^�C�v
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass,DIR stdir, cocos2d::Vec2 pos, cocos2d::Vec2 speed, cocos2d::Scene *scene);

	void SetDBBox(Sprite* sp);												//	�f�o�b�O���̓����蔻��pBox��Set

private:
	void InitActData(cocos2d::Vec2 speed);									//	ActData�̏�����

protected:
	OprtState *_oprtState;													//	���쐧��
	ActData _actData;														//	�L�����N�^�[�̏��p
	std::map<const char *,ActData> _charaList;								//	�L�����N�^�[�̏��p���X�g

	Sprite *_box;															//	�����蔻��p��BOX

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;					//	�L�[�p�̃��X�g

	//std::list<actionPoint> _actList;										//	�A�N�V�����̊Ǘ��p

	//bool(*_act)(cocos2d::Sprite&, ActData &);								//	�֐��|�C���^
};
