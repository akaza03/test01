#include "OprtKey.h"
#include "OprtTouch.h"
#include "_DebugConOut.h"
#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, cocos2d::Vec2 speed, cocos2d::Scene *scene)
{
	InitActData(speed);
	auto sprite = Sprite::create(ImagePass);
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	//	�v���b�g�t�H�[���ɂ���đ�����@��ς���
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}
	//	����C�x���g�̍쐬
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this),scene);
}

void Character::InitActData(cocos2d::Vec2 speed)
{
	//	�L�����N�^�[�̏��̒ǉ�
	_actData.speed = speed;
	_actData.key[UseKey::K_LEFT] = std::make_pair(false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_pair(false, true);
	_actData.key[UseKey::K_UP] = std::make_pair(false, true);
	_actData.key[UseKey::K_DOWN] = std::make_pair(false, true);
	_actData.checkPoint[DIR::LEFT] = false;
	_actData.checkPoint[DIR::RIGHT] = false;
	_actData.checkPoint[DIR::UP] = false;
	_actData.checkPoint[DIR::DOWN] = false;
	_actData.anim = AnimState::IDLE;
	_charaList.emplace(std::make_pair("idle", _actData));
	_actData.anim = AnimState::RUN;
	_charaList.emplace(std::make_pair("run", _actData));
	_actData.anim = AnimState::RSHOT;
	_charaList.emplace(std::make_pair("pShot", _actData));
	_actData.anim = AnimState::SHOTUP;
	_charaList.emplace(std::make_pair("shotUp", _actData));
	_actData.anim = AnimState::STAND;
	_charaList.emplace(std::make_pair("stand", _actData));
	_actData.anim = AnimState::JUMP;
	_actData.key[UseKey::K_DOWN].second = false;
	_charaList.emplace(std::make_pair("jump", _actData));
	_actData.anim = AnimState::CLING;
	_charaList.emplace(std::make_pair("cling", _actData));
	_actData.anim = AnimState::DUCK;
	_charaList.emplace(std::make_pair("duck", _actData));
	_actData.anim = AnimState::HURT;
	_charaList.emplace(std::make_pair("hurt", _actData));

	lpAnimManager.AnimRun(this, _charaList["idle"].nowAnim, _charaList["idle"].cType);
}

void Character::SetDBBox(Sprite * sp)
{
#ifdef _DEBUG
	//	�����蔻��p�̎l�p�`��
	_box = sp;
#endif // _DEBUG
}
