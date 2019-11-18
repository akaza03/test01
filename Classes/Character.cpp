#include "OprtKey.h"
#include "OprtTouch.h"
#include "_DebugConOut.h"
#include "Character.h"


Character::Character()
{
	_state = AnimState::IDLE;
	_oldState = AnimState::STATE_MAX;
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
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}
	//	����C�x���g�̍쐬
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this, speed, this),scene);
}

void Character::InitActData(int speed)
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
}

void Character::SetDBBox(Sprite * sp)
{
#ifdef _DEBUG
	//	�����蔻��p�̎l�p�`��
	_box = sp;
#endif // _DEBUG
}


//void Character::CheckCol()
//{
//	//	�d�͂����Z����
//	float gy = -0.05f;
//	_Gravity += gy;
//	bool GyFlag = false;
//
//	//	�Փ˗p�̃��C���[�̎擾
//	auto director = cocos2d::Director::getInstance();
//	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
//	auto layerMap = map->getLayer("collision");
//
//	//	�v���C���[�̍��W
//	auto pos = cocos2d::Vec2(getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - getPosition().y);
//	//	�w�肳�ꂽ�ꏊ�̃^�C��ID
//	int tile = 0;
//
//	//	�}�b�v�Ƃ̓����蔻��
//	//	��
//	//auto DownPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height + 1);
//	//tile = GetTile(DownPos, layerMap);
//	//if (tile != 0)
//	//{
//	//	TRACE("��%d", tile);
//	//	_Gravity = 0;
//	//	if (!_JumpStart)
//	//	{
//	//		_movePos.y = 0;
//	//		_moveFlagY = false;
//	//	}
//
//	//	if (_movePos.y <= 0)
//	//	{
//	//		_movePos.y = 0;
//	//	}
//	//}
//	//	��
//	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
//	tile = GetTile(UpPos, layerMap);
//	if (tile != 0)
//	{
//		_Gravity = gy * 10;
//		TRACE("��%d", tile);
//		if (_movePos.y > 0)
//		{
//			_movePos.y = 0;
//		}
//	}
//	// ��
//	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
//	tile = GetTile(LPos, layerMap);
//	if (tile != 0)
//	{ 
//		TRACE("��%d", tile);
//		if (_movePos.x < 0)
//		{
//			_movePos.x = 0;
//		}
//	}
//	//	�E
//	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
//	tile = GetTile(RPos, layerMap);
//	if (tile != 0)
//	{
//		TRACE("�E%d", tile);
//		if (_movePos.x > 0)
//		{
//			_movePos.x = 0;
//		}
//	}
//}
//
//int Character::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer)
//{
//	//	�擾�ꏊ����ʊO�̏ꍇ��0��Ԃ�
//	if (_pos.x > 0 && _pos.x < _layer->getLayerSize().width
//		&&	_pos.y > 0 && _pos.y < _layer->getLayerSize().height)
//	{
//		//	�^�C���̎擾
//		return _layer->getTileGIDAt(_pos);
//	}
//	return 0;
//}
//
//void Character::dirUpdate()
//{
//	//	�v���C���[�̌����̍X�V
//	if (_oldPos.x > getPosition().x)
//	{
//		_charaDir = DIR::LEFT;
//	}
//	else if (_oldPos.x < getPosition().x)
//	{
//		_charaDir = DIR::RIGHT;
//	}
//
//	_oldPos = getPosition();
//
//	if (_charaDir != _oldDir)
//	{
//		if (_charaDir != _startDir)
//		{
//			setFlippedX(true);
//		}
//		else
//		{
//			setFlippedX(false);
//		}
//	}
//	_oldDir = _charaDir;
//}
//
//void Character::moveUpdate()
//{
//	_JumpStart = false;
//	//	�ړ�
//	if (_moveFlagX)
//	{
//		setPosition(getPosition().x + _movePos.x, getPosition().y);
//	}
//	if (_moveFlagY)
//	{
//		setPosition(getPosition().x, getPosition().y + _movePos.y);
//	}
//}
//
//void Character::AnimStateUpdate()
//{
//	//	AnimState�̍X�V
//	if (_moveFlagY)
//	{
//		_state = AnimState::JUMP;
//	}
//	else if (_moveFlagX)
//	{
//		_state = AnimState::RUN;
//	}
//	else
//	{
//		_state = AnimState::IDLE;
//	}
//
//	//	�A�j���[�V�����̍X�V
//	if (_state != _oldState)
//	{
//		lpAnimManager.AnimRun(this, _actData.anim, _cType);
//	}
//	_oldState = _state;
//}
