#pragma once
#include <map>
#include "cocos2d.h"
#include "Character.h"

#define lpAnimManager AnimManager::GetInstance()

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

	cocos2d::Action* GetAnim(std::string actionName);

	//	�A�j���[�V�����̊J�n
	void AnimRun(cocos2d::Sprite* sprite, std::string actionName);
private:
	AnimManager();
	//	�A�j���[�V�����̓o�^�p
	void AnimationInit();

	//	�Q�ƃJ�E���g�𑝂₷
	void AnimCountPlus();

	std::map < std::string, cocos2d::Action* > animMap;
	static AnimManager* s_Instance;
};
