#include "Player.h"
#include "_DebugConOut.h"

Player::Player()
{
	//Sprite::create("image/Sprites/player/player-idle/player-idle-1.png");

	//charaDir = DIR::RIGHT;
	//startDir = charaDir;
	//OldDir = charaDir;

	state = AnimState::IDLE;
	oldState = AnimState::STATE_MAX;
	movePos = cocos2d::Vec2(0, 0);

	this->scheduleUpdate();
}

Player::~Player()
{
}

void Player::update(float d)
{
	colMovePos = movePos;
	CheckCol();

	if (moveFlag)
	{
		setPosition(getPosition() + colMovePos);
	}

	if (charaDir != OldDir)
	{
		if (charaDir != startDir)
		{
			setFlippedX(true);
		}
		else
		{
			setFlippedX(false);
		}
		
	}
	OldDir = charaDir;

	if (state != oldState)
	{
		switch (state)
		{
		case AnimState::IDLE:
			lpAnimManager.AnimRun(this, "p_idle");
			break;
		case AnimState::RUN:
			lpAnimManager.AnimRun(this, "p_run");
			break;
		case AnimState::SHOTUP:
			lpAnimManager.AnimRun(this, "p_shotUp");
			break;
		case AnimState::STAND:
			lpAnimManager.AnimRun(this, "p_stand");
			break;
		case AnimState::JUMP:
			lpAnimManager.AnimRun(this, "p_jump");
			break;
		case AnimState::CLING:
			lpAnimManager.AnimRun(this, "p_cling");
			break;
		case AnimState::DUCK:
			lpAnimManager.AnimRun(this, "p_duck");
			break;
		case AnimState::HURT:
			lpAnimManager.AnimRun(this, "p_hurt");
			break;
		case AnimState::STATE_MAX:
			break;
		default:
			break;
		}
	}

	oldState = state;
}

void Player::SetDBBox(Sprite* sp)
{
#ifdef _DEBUG
	//	当たり判定用の四角描画
	box = sp;
#endif // _DEBUG
}

void Player::CheckCol()
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
		if (colMovePos.y < 0)
		{
			colMovePos.y = 0;
		}
	}
	//	上
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		TRACE("上%d", tile);
		if (colMovePos.y > 0)
		{
			colMovePos.y = 0;
		}
	}
	// 左
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{
		TRACE("左%d", tile);
		if (colMovePos.x < 0)
		{
			colMovePos.x = 0;
		}
	}
	//	右
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if(tile != 0)
	{
		TRACE("右%d", tile);
		if (colMovePos.x > 0)
		{
			colMovePos.x = 0;
		}
	}

	//	重力を座標に加算する
	setPosition(getPosition().x, getPosition().y + Gy);

	//	デバッグ用Boxの座標設定
#ifdef _DEBUG
	//VecLU.x = VecLU.x * layerMap->getMapTileSize().width + getContentSize().width / 2;
	//VecLU.y = (layerMap->getLayerSize().height - VecLU.y) * layerMap->getMapTileSize().height - getContentSize().height / 2;

	box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	box->setPosition(getPosition());
#endif // _DEBUG

}

int Player::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer)
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


