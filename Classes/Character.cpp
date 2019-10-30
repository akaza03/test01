#include "Character.h"

#include "OprtKey.h"
#include "OprtTouch.h"
#include "_DebugConOut.h"


Character::Character()
{
	moveFlagX = false;
	moveFlagY = false;
	Gy = 0;
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene)
{
	auto sprite = Sprite::create(ImagePass);

	charaDir = stdir;
	startDir = charaDir;
	OldDir = charaDir;

	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));
	this->speed = speed;

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

AnimState Character::GetState()
{
	return state;
}

void Character::SetState(AnimState st)
{
	state = st;
}

DIR Character::GetDir()
{
	return charaDir;
}

void Character::SetDir(DIR dir)
{
	charaDir = dir;
}

void Character::SetSpeed(int sp)
{
	speed = sp;
}

int Character::GetSpeed()
{
	return speed;
}

void Character::SetMoveFlagX(bool flag)
{
	moveFlagX = flag;
}

void Character::SetMoveFlagY(bool flag)
{
	moveFlagY = flag;
}

bool Character::GetMoveFlagX()
{
	return moveFlagX;
}

bool Character::GetMoveFlagY()
{
	return moveFlagY;
}

cocos2d::Vec2 Character::GetMovePos()
{
	return movePos;
}

void Character::SetMovePosX(float pos)
{
	movePos.x = pos;
}

void Character::SetMovePosY(float pos)
{
	movePos.y = pos;
}

void Character::SetJumpStart(bool flag)
{
	JumpStart = flag;
}


void Character::CheckCol()
{
	//	重力を加算する
	float g = -0.05f;
	Gy += g;
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
		Gy = 0;
		if (!JumpStart)
		{
			movePos.y = 0;
			moveFlagY = false;
		}

		if (movePos.y <= 0)
		{
			movePos.y = 0;
		}
	}
	else
	{
		moveFlagY = true;
	}
	//	上
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		Gy = g * 10;
		TRACE("上%d", tile);
		if (movePos.y > 0)
		{
			movePos.y = 0;
		}
	}
	// 左
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{ 
		TRACE("左%d", tile);
		if (movePos.x < 0)
		{
			movePos.x = 0;
		}
	}
	//	右
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if (tile != 0)
	{
		TRACE("右%d", tile);
		if (movePos.x > 0)
		{
			movePos.x = 0;
		}
	}

	//	重力を座標に加算する
	setPosition(getPosition().x, getPosition().y + Gy);

	//	デバッグ用Boxの座標設定
#ifdef _DEBUG
	box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	box->setPosition(getPosition());
#endif // _DEBUG

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
