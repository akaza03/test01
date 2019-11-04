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
	_animMap["p_idle"] = AnimationCreate(pass + "player-idle/player-idle.plist", 4, 0.5f, "player-idle-%i.png", true);
	_animMap["p_run"] = AnimationCreate(pass + "player-run/player-run.plist", 10, 0.1f, "player-run-%i.png", true);
	_animMap["p_runShot"] = AnimationCreate(pass + "player-run-shot/player-run-shot.plist", 10, 0.3f, "player-run-shot-%i.png", true);
	_animMap["p_shotUp"] = AnimationCreate(pass + "player-shoot-up/player-shoot-up.plist", 1, 1, "player-shoot-up-%i.png", true);
	_animMap["p_stand"] = AnimationCreate(pass + "player-stand/player-stand.plist", 3, 0.5f, "player-stand-%i.png", true);
	_animMap["p_jump"] = AnimationCreate(pass + "player-jump/player-jump.plist", 6, 0.5f, "player-jump-%i.png", true);
	_animMap["p_cling"] = AnimationCreate(pass + "player-cling/player-cling.plist", 1, 1, "player-cling-%i.png", true);
	_animMap["p_duck"] = AnimationCreate(pass + "player-duck/player-duck.plist", 1, 1, "player-duck-%i.png", true);
	_animMap["p_hurt"] = AnimationCreate(pass + "player-hurt/player-hurt.plist", 2, 1.0f, "player-hurt-%i.png", true);

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
}

void AnimManager::AnimRun(cocos2d::Sprite * sprite, AnimState anim, CharaType type)
{
	auto animName = GetAnimName(anim, type);

	auto action = _animMap[animName];
	if (action != nullptr)
	{
		sprite->stopAllActions();
		sprite->runAction(_animMap[animName]);
	}
	AnimCountPlus();
}

void AnimManager::AnimCountPlus()
{
	_animMap["p_idle"]->retain();
	_animMap["p_run"]->retain();
	_animMap["p_runShot"]->retain();
	_animMap["p_shotUp"]->retain();
	_animMap["p_stand"]->retain();
	_animMap["p_jump"]->retain();
	_animMap["p_cling"]->retain();
	_animMap["p_duck"]->retain();
	_animMap["p_hurt"]->retain();
}

std::string AnimManager::GetAnimName(AnimState anim, CharaType type)
{
	switch (type)
	{
	case CharaType::PLAYER:
		switch (anim)
		{
		case IDLE:
			return "p_idle";
			break;
		case RUN:
			return "p_run";
			break;
		case RSHOT:
			return "p_runShot";
			break;
		case SHOTUP:
			return "p_shotUp";
			break;
		case STAND:
			return "p_stand";
			break;
		case JUMP:
			return "p_jump";
			break;
		case CLING:
			return "p_cling";
			break;
		case DUCK:
			return "p_duck";
			break;
		case HURT:
			return "p_hurt";
			break;
		case STATE_MAX:
			break;
		default:
			break;
		}
		break;
	case CharaType::ENEMY:
		switch (anim)
		{
		case IDLE:
			break;
		case RUN:
			break;
		case RSHOT:
			break;
		case SHOTUP:
			break;
		case STAND:
			break;
		case JUMP:
			break;
		case CLING:
			break;
		case DUCK:
			break;
		case HURT:
			break;
		case STATE_MAX:
			break;
		default:
			break;
		}
		break;
	case CharaType::CHARA_MAX:
		break;
	default:
		break;
	}
	return "‚È‚µ";
}
