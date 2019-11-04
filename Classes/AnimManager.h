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
	//	コンストラクタにてアニメーションの登録
	cocos2d::Action* AnimationCreate(std::string plistPass, int ImageMax, float FCount, const char* ImageNameN, bool loop);

	void AnimRun(cocos2d::Sprite* sprite, AnimState anim, CharaType type);		//	アニメーションの開始
private:
	AnimManager();
	void AnimationInit();														//	アニメーションの登録用

	std::string GetAnimName(AnimState anim, CharaType type);					//	アニメーション開始時のアニメーション名取得用

	void AnimCountPlus();														//	参照カウントを増やす

	std::map < std::string, cocos2d::Action* > _animMap;						//	アニメーション情報を収納
	static AnimManager* s_Instance;
};
