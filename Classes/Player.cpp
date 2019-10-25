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

	//	プレイヤーの頂点をタイルマップの座標に置き換える

	//	プレイヤーの画像サイズ(マス数)
	cocos2d::Size ImageSize;
	ImageSize.width = getContentSize().width / layerMap->getMapTileSize().width;
	ImageSize.height = getContentSize().height / layerMap->getMapTileSize().height;

	//	プレイヤーの左上の座標
	cocos2d::Vec2 LUPos = cocos2d::Vec2(getPosition().x - getContentSize().width / 2, getPosition().y + getContentSize().height / 2);

	//	指定された場所のタイルID
	int tile = 0;

	//	左上
	cocos2d::Vec2 VecLU = cocos2d::Vec2(LUPos.x / layerMap->getMapTileSize().width, LUPos.y / layerMap->getMapTileSize().height);
	VecLU.y = layerMap->getLayerSize().height - VecLU.y;
	//	判定
	tile = layerMap->getTileGIDAt(VecLU);
	if (tile != 0)
	{
		//TRACE("\n左上hit%d\n", tile);
		if (movePos.y > 0)
		{
			colMovePos.y = 0;
		}
	}
	//	左下
	auto VecLD = VecLU;
	VecLD.y = VecLU.y + ImageSize.height;
	tile = layerMap->getTileGIDAt(VecLD);
	if (tile != 0)
	{
		//TRACE("\n左下hit%d\n", tile);
		if (movePos.y < 0)
		{
			colMovePos.y = 0;
		}
		Gy = 0;
	}

	//	左中央
	auto VecLC = VecLU;
	VecLC.y = VecLC.y + ImageSize.height / 2;
	if (tile != 0)
	{
		TRACE("\n左中央hit%d\n", tile);
		//if (movePos.x < 0)
		//{
		//	colMovePos.x = 0;
		//}
		//if (movePos.y < 0)
		//{
		//	colMovePos.y = 0;
		//}
	}

	//	右上
	auto VecRU = VecLU;
	VecRU.x = VecLU.x + ImageSize.width;
	tile = layerMap->getTileGIDAt(VecRU);
	if (tile != 0)
	{
		//TRACE("\n右上hit%d\n", tile);
		if (movePos.y > 0)
		{
			colMovePos.y = 0;
		}
	}
	//	右下
	auto VecRD = VecLU;
	VecRD.x = VecLU.x + ImageSize.width;
	VecRD.y = VecLU.y + ImageSize.height;
	tile = layerMap->getTileGIDAt(VecRD);
	if (tile != 0)
	{
		//TRACE("\n右下hit%d\n", tile);
		if (movePos.y < 0)
		{
			colMovePos.y = 0;
		}
		Gy = 0;
	}

	//	右中央
	auto VecRC = VecRU;
	VecRC.y = VecRC.y + ImageSize.height / 2;
	tile = layerMap->getTileGIDAt(VecRC);
	if (tile != 0)
	{
		TRACE("\n右中央hit%d\n", tile);
		//if (movePos.x < 0)
		//{
		//	colMovePos.x = 0;
		//}
		//if (movePos.y < 0)
		//{
		//	colMovePos.y = 0;
		//}
	}

	//	画面外に移動しないように
	//	左移動時
	if (movePos.x < 0)
	{
		if (VecLU.x + (movePos.x - getContentSize().width) / layerMap->getMapTileSize().width <= 0)
		{
			colMovePos.x = -getPosition().x + getContentSize().width;
		}
	}
	////	右移動時
	//if (movePos.x > 0)
	//{
	//	if (VecRU.x + (movePos.x + getContentSize().width / 2) / layerMap->getMapTileSize().width >= layerMap->getLayerSize().width)
	//	{
	//		colMovePos.x = layerMap->getLayerSize().width * layerMap->getMapTileSize().width - getPosition().x - getContentSize().width / 2;
	//	}
	//}

	////	上移動時
	//if (movePos.y > 0)
	//{
	//	if (layerMap->getLayerSize().height - (VecLU.y + (movePos.y - getContentSize().height / 2) / layerMap->getMapTileSize().height) <= 0)
	//	{
	//		colMovePos.y = getPosition().y - getContentSize().height / 2;
	//	}
	//}
	////	下移動時
	//if (movePos.y < 0)
	//{
	//	if (VecLD.y * layerMap->getMapTileSize().height + (-movePos.y + getContentSize().height / 2) >= layerMap->getLayerSize().height * layerMap->getMapTileSize().height)
	//	{
	//		colMovePos.y = -getPosition().y + getContentSize().height / 2;
	//	}
	//}

	//	重力を座標に加算する
	setPosition(getPosition().x, getPosition().y + Gy);

	//	デバッグ用Boxの座標設定
#ifdef _DEBUG
	VecLU.x = VecLU.x * layerMap->getMapTileSize().width + getContentSize().width / 2;
	VecLU.y = (layerMap->getLayerSize().height - VecLU.y) * layerMap->getMapTileSize().height - getContentSize().height / 2;

	box->setTextureRect(cocos2d::Rect(VecLU.x, VecLU.y, getContentSize().width, getContentSize().height));
	box->setPosition(VecLU);
#endif // _DEBUG

}


