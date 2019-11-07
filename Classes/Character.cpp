#include "OprtKey.h"
#include "OprtTouch.h"
#include "_DebugConOut.h"
#include "Character.h"


Character::Character()
{
	_charaID.anim = AnimState::IDLE;
	_oldState = AnimState::STATE_MAX;
	_movePos = cocos2d::Vec2(0, 0);

	_moveFlagX = false;
	_moveFlagY = false;
	_Gravity = 0;
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene)
{
	InitCharaID(speed);
	SetCharaType();
	auto sprite = Sprite::create(ImagePass);
	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));


	_charaDir = stdir;
	_startDir = _charaDir;
	_oldDir = _charaDir;
	_oldPos = pos;



	this->_speed = speed;

	//	プラットフォームによって操作方法を変える
	if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	{
		_oprtState = new OprtKey();
	}
	else
	{
		_oprtState = new OprtTouch();
	}



	//	操作イベントの作成
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this, speed, this),scene);
}

void Character::InitCharaID(int speed)
{
	//	キャラクターの情報の追加
	_charaID.speed = speed;
	_charaID.key[cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = std::make_pair(false, false);
	_charaID.key[cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW] = std::make_pair(false, false);
	_charaID.key[cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW] = std::make_pair(false, false);
	_charaID.key[cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW] = std::make_pair(false, false);
	_charaID.anim = AnimState::IDLE;
	_charaList.insert(std::make_pair("idle", _charaID));
	_charaID.anim = AnimState::RUN;
	_charaList.insert(std::make_pair("run", _charaID));
	_charaID.anim = AnimState::RSHOT;
	_charaList.insert(std::make_pair("pShot", _charaID));
	_charaID.anim = AnimState::SHOTUP;
	_charaList.insert(std::make_pair("shotUp", _charaID));
	_charaID.anim = AnimState::STAND;
	_charaList.insert(std::make_pair("stand", _charaID));
	_charaID.anim = AnimState::JUMP;
	_charaList.insert(std::make_pair("jump", _charaID));
	_charaID.anim = AnimState::CLING;
	_charaList.insert(std::make_pair("cling", _charaID));
	_charaID.anim = AnimState::DUCK;
	_charaList.insert(std::make_pair("duck", _charaID));
	_charaID.anim = AnimState::HURT;
	_charaList.insert(std::make_pair("hurt", _charaID));
}

AnimState Character::GetState()
{
	return _state;
}

void Character::SetState(AnimState st)
{
	_state = st;
}

DIR Character::GetDir()
{
	return _charaDir;
}

void Character::SetDir(DIR dir)
{
	_charaDir = dir;
}

void Character::SetSpeed(int sp)
{
	_speed = sp;
}

int Character::GetSpeed()
{
	return _speed;
}

void Character::SetMoveFlagX(bool flag)
{
	_moveFlagX = flag;
}

void Character::SetMoveFlagY(bool flag)
{
	_moveFlagY = flag;
}

bool Character::GetMoveFlagX()
{
	return _moveFlagX;
}

bool Character::GetMoveFlagY()
{
	return _moveFlagY;
}

cocos2d::Vec2 Character::GetMovePos()
{
	return _movePos;
}

void Character::SetMovePosX(float pos)
{
	_movePos.x = pos;
}

void Character::SetMovePosY(float pos)
{
	_movePos.y = pos;
}

void Character::SetJumpStart(bool flag)
{
	_JumpStart = flag;
}

CharaType Character::GetCharaType()
{
	return _cType;
}

void Character::SetDBBox(Sprite * sp)
{
#ifdef _DEBUG
	//	当たり判定用の四角描画
	_box = sp;
#endif // _DEBUG
}


void Character::CheckCol()
{
	//	重力を加算する
	float gy = -0.05f;
	_Gravity += gy;
	bool GyFlag = false;

	//	衝突用のレイヤーの取得
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	プレイヤーの座標
	auto pos = cocos2d::Vec2(getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - getPosition().y);
	//	指定された場所のタイルID
	int tile = 0;

	//	マップとの当たり判定
	//	下
	auto DownPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height + 1);
	tile = GetTile(DownPos, layerMap);
	if (tile != 0)
	{
		TRACE("下%d", tile);
		_Gravity = 0;
		if (!_JumpStart)
		{
			_movePos.y = 0;
			_moveFlagY = false;
		}

		if (_movePos.y <= 0)
		{
			_movePos.y = 0;
		}
	}
	//	上
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		_Gravity = gy * 10;
		TRACE("上%d", tile);
		if (_movePos.y > 0)
		{
			_movePos.y = 0;
		}
	}
	// 左
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{ 
		TRACE("左%d", tile);
		if (_movePos.x < 0)
		{
			_movePos.x = 0;
		}
	}
	//	右
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if (tile != 0)
	{
		TRACE("右%d", tile);
		if (_movePos.x > 0)
		{
			_movePos.x = 0;
		}
	}
}

int Character::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer)
{
	//	取得場所が画面外の場合は0を返す
	if (_pos.x > 0 && _pos.x < _layer->getLayerSize().width
		&&	_pos.y > 0 && _pos.y < _layer->getLayerSize().height)
	{
		//	タイルの取得
		return _layer->getTileGIDAt(_pos);
	}
	return 0;
}

void Character::dirUpdate()
{
	//	プレイヤーの向きの更新
	if (_oldPos.x > getPosition().x)
	{
		_charaDir = DIR::LEFT;
	}
	else if (_oldPos.x < getPosition().x)
	{
		_charaDir = DIR::RIGHT;
	}

	_oldPos = getPosition();

	if (_charaDir != _oldDir)
	{
		if (_charaDir != _startDir)
		{
			setFlippedX(true);
		}
		else
		{
			setFlippedX(false);
		}
	}
	_oldDir = _charaDir;
}

void Character::moveUpdate()
{
	_JumpStart = false;
	//	移動
	if (_moveFlagX)
	{
		setPosition(getPosition().x + _movePos.x, getPosition().y);
	}
	if (_moveFlagY)
	{
		setPosition(getPosition().x, getPosition().y + _movePos.y);
	}
}

void Character::AnimStateUpdate()
{
	////	AnimStateの更新
	//if (_moveFlagY)
	//{
	//	_state = AnimState::JUMP;
	//}
	//else if (_moveFlagX)
	//{
	//	_state = AnimState::RUN;
	//}
	//else
	//{
	//	_state = AnimState::IDLE;
	//}

	////	アニメーションの更新
	//if (_state != _oldState)
	//{
	//	lpAnimManager.AnimRun(this, _charaID.anim, _cType);
	//}
	//_oldState = _state;
}
