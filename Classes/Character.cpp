#include "OprtKey.h"
#include "OprtTouch.h"
#include "_DebugConOut.h"
#include "Character.h"


Character::Character()
{
	_Gravity = 0;
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene)
{
	InitActData(speed);
	auto sprite = Sprite::create(ImagePass);
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));

	//	�v���b�g�t�H�[���ɂ���đ�����@��ς���
	//if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	//{
	//	_oprtState = new OprtKey();
	//}
	//else
	{
		_oprtState = new OprtTouch();
	}
	//	����C�x���g�̍쐬
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this, speed),scene);
}

void Character::InitActData(int speed)
{
	//	�L�����N�^�[�̏��̒ǉ�
	_actData.speed = speed;
	_actData.dir = DIR::RIGHT;
	_actData.distance = cocos2d::Vec2(0, 0);
	_actData.key[UseKey::K_LEFT] = std::make_pair(false, true);
	_actData.key[UseKey::K_RIGHT] = std::make_pair(false, true);
	_actData.key[UseKey::K_UP] = std::make_pair(false, true);
	_actData.key[UseKey::K_DOWN] = std::make_pair(false, true);
	_actData.checkPoint[DIR::LEFT] = false;
	_actData.checkPoint[DIR::RIGHT] = false;
	_actData.checkPoint[DIR::UP] = false;
	_actData.checkPoint[DIR::DOWN] = false;
	_actData.anim = AnimState::IDLE;
	_charaList.insert(std::make_pair("idle", _actData));
	_actData.anim = AnimState::RUN;
	_charaList.insert(std::make_pair("run", _actData));
	_actData.anim = AnimState::RSHOT;
	_charaList.insert(std::make_pair("pShot", _actData));
	_actData.anim = AnimState::SHOTUP;
	_charaList.insert(std::make_pair("shotUp", _actData));
	_actData.anim = AnimState::STAND;
	_charaList.insert(std::make_pair("stand", _actData));
	_actData.anim = AnimState::JUMP;
	_actData.key[UseKey::K_DOWN].second = false;
	_charaList.insert(std::make_pair("jump", _actData));
	_actData.anim = AnimState::CLING;
	_charaList.insert(std::make_pair("cling", _actData));
	_actData.anim = AnimState::DUCK;
	_charaList.insert(std::make_pair("duck", _actData));
	_actData.anim = AnimState::HURT;
	_charaList.insert(std::make_pair("hurt", _actData));

	for (auto &cList:_charaList)
	{
		cList.second.nowAnim = AnimState::IDLE;
	}

	lpAnimManager.AnimRun(this, _charaList["idle"].nowAnim, _charaList["idle"].cType);
}

void Character::SetDBBox(Sprite * sp)
{
#ifdef _DEBUG
	//	�����蔻��p�̎l�p�`��
	_box = sp;
#endif // _DEBUG
}
