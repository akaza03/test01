#pragma once
#include <map>
#include "cocos2d.h"
#include "charaStruct.h"
#include "Character.h"

#define lpAnimManager AnimManager::GetInstance()

class Character;

class AnimManager
{
public:
	static AnimManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AnimManager();
		}
		return *s_Instance;
	}
	~AnimManager();
	//	�R���X�g���N�^�ɂăA�j���[�V�����̓o�^
	cocos2d::Action* AnimationCreate(std::string plistPass, int ImageMax, float FCount, const char* ImageNameN, bool loop);

	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type);		//	�A�j���[�V�����̊J�n
private:
	AnimManager();
	void AnimationInit();														//	�A�j���[�V�����̓o�^�p

	std::string GetAnimName(AnimState anim, CharaType type);					//	�A�j���[�V�����J�n���̃A�j���[�V�������擾�p

	void AnimCountPlus();														//	�Q�ƃJ�E���g�𑝂₷

	std::map < std::string, cocos2d::Action* > _animMap;						//	�A�j���[�V�����������[
	static AnimManager* s_Instance;
};
