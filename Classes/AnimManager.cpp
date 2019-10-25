#include "AnimManager.h"

AnimManager* AnimManager::s_Instance = nullptr;

AnimManager::AnimManager()
{
	AnimationInit();
}


AnimManager::~AnimManager()
{

}

void AnimManager::AnimationInit()
{
	std::string pass = "image/Sprites/player/";
	animMap["p_idle"] = AnimationCreate(pass + "player-idle/player-idle.plist", 4, 0.5f, "player-idle-%i.png", true);
	animMap["p_run"] = AnimationCreate(pass + "player-run/player-run.plist", 10, 0.1f, "player-run-%i.png", true);
	animMap["p_runShot"] = AnimationCreate(pass + "player-run-shot/player-run-shot.plist", 10, 0.3f, "player-run-shot-%i.png", true);
	animMap["p_shotUp"] = AnimationCreate(pass + "player-shoot-up/player-shoot-up.plist", 1, 0, "player-shoot-up-%i.png", true);
	animMap["p_stand"] = AnimationCreate(pass + "player-stand/player-stand.plist", 3, 0.5f, "player-stand-%i.png", true);
	animMap["p_jump"] = AnimationCreate(pass + "player-jump/player-jump.plist", 6, 0.2f, "player-jump-%i.png", true);
	animMap["p_cling"] = AnimationCreate(pass + "player-cling/player-cling.plist", 1, 0, "player-cling-%i.png", true);
	animMap["p_duck"] = AnimationCreate(pass + "player-duck/player-duck.plist", 1, 0, "player-duck-%i.png", true);
	animMap["p_hurt"] = AnimationCreate(pass + "player-hurt/player-hurt.plist", 2, 1.0f, "player-hurt-%i.png", true);

	pass = "image/Sprites/enemies/";
}


cocos2d::Action* AnimManager::AnimationCreate(std::string plistPass,int ImageMax, float FCount, const char* ImageNameN, bool loop)
{
	//	‰æ‘œ‚Ì“Ç‚Ýž‚Ý
	auto cache = cocos2d::SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(plistPass);
	auto _animation = cocos2d::Animation::create();

	//	‰æ‘œ‚ð”z—ñ‚É‘ã“ü
	for (int i = 1; i < ImageMax + 1; i++)
	{
		//auto str = cocos2d::__String::createWithFormat("player-idle-%i.png", i - 1);
		auto str = cocos2d::__String::createWithFormat(ImageNameN, i);
		
		cocos2d::SpriteFrame *spFrame = cache->getSpriteFrameByName(str->getCString());
		_animation->addSpriteFrame(spFrame);
	}

	_animation->setDelayPerUnit(FCount);
	_animation->setRestoreOriginalFrame(true);

	auto animate = cocos2d::Animate::create(_animation);

	//	ƒ‹[ƒv‚·‚é‚©‚Ç‚¤‚©‚Ìˆ—
	if (loop)
	{
		return cocos2d::RepeatForever::create(animate);
	}
	return animate;
	
	//auto action = cocos2d::RepeatForever::create(animate);
	//return sprite->runAction(action);
}

cocos2d::Action * AnimManager::GetAnim(std::string actionName)
{
	return animMap[actionName];
}

void AnimManager::AnimRun(cocos2d::Sprite * sprite, std::string actionName)
{
	auto action = animMap[actionName];
	if(action != nullptr)
	{
		sprite->stopAllActions();
		sprite->runAction(animMap[actionName]);
	}
	AnimCountPlus();
}

void AnimManager::AnimCountPlus()
{
	animMap["p_idle"]->retain();
	animMap["p_run"]->retain();
	animMap["p_runShot"]->retain();
	animMap["p_shotUp"]->retain();
	animMap["p_stand"]->retain();
	animMap["p_jump"]->retain();
	animMap["p_cling"]->retain();
	animMap["p_duck"]->retain();
	animMap["p_hurt"]->retain();
}
