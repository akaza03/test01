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
	//	�����蔻��p�̎l�p�`��
	box = sp;
#endif // _DEBUG
}

void Player::CheckCol()
{
	//	�d�͂����Z����
	float g = -0.05f;
	Gy += g;
	bool GyFlag = false;

	//	�Փ˗p�̃��C���[�̎擾
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	�v���C���[�̍��W
	auto pos = cocos2d::Vec2(getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - getPosition().y);
	//	�w�肳�ꂽ�ꏊ�̃^�C��ID
	int tile = 0;

	//	�}�b�v�Ƃ̓����蔻��
	//	��
	auto DownPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height + 1);
	tile = GetTile(DownPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		Gy = 0;
		if (colMovePos.y < 0)
		{
			colMovePos.y = 0;
		}
	}
	//	��
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		if (colMovePos.y > 0)
		{
			colMovePos.y = 0;
		}
	}
	// ��
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		if (colMovePos.x < 0)
		{
			colMovePos.x = 0;
		}
	}
	//	�E
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if(tile != 0)
	{
		TRACE("�E%d", tile);
		if (colMovePos.x > 0)
		{
			colMovePos.x = 0;
		}
	}

	//	�d�͂����W�ɉ��Z����
	setPosition(getPosition().x, getPosition().y + Gy);

	//	�f�o�b�O�pBox�̍��W�ݒ�
#ifdef _DEBUG
	//VecLU.x = VecLU.x * layerMap->getMapTileSize().width + getContentSize().width / 2;
	//VecLU.y = (layerMap->getLayerSize().height - VecLU.y) * layerMap->getMapTileSize().height - getContentSize().height / 2;

	box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	box->setPosition(getPosition());
#endif // _DEBUG

}

int Player::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer)
{
	//	�擾�ꏊ����ʊO�̏ꍇ��0��Ԃ�
	if (_pos.x > 0 && _pos.x < _layer->getLayerSize().width
		&&	_pos.y > 0 && _pos.y < _layer->getLayerSize().height)
	{
		//	�^�C���̎擾
		return _layer->getTileGIDAt(_pos);
	}
	return 0;
}


