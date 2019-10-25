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
	//	コンストラクタにてアニメーションの登録
	cocos2d::Action* AnimationCreate(std::string plistPass, int ImageMax, float FCount, const char* ImageNameN, bool loop);

	cocos2d::Action* GetAnim(std::string actionName);

	//	アニメーションの開始
	void AnimRun(cocos2d::Sprite* sprite, std::string actionName);
private:
	AnimManager();
	//	アニメーションの登録用
	void AnimationInit();

	//	参照カウントを増やす
	void AnimCountPlus();

	std::map < std::string, cocos2d::Action* > animMap;
	static AnimManager* s_Instance;
};
