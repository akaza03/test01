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
	//	��
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		Gy = g * 10;
		TRACE("��%d", tile);
		if (movePos.y > 0)
		{
			movePos.y = 0;
		}
	}
	// ��
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{ 
		TRACE("��%d", tile);
		if (movePos.x < 0)
		{
			movePos.x = 0;
		}
	}
	//	�E
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if (tile != 0)
	{
		TRACE("�E%d", tile);
		if (movePos.x > 0)
		{
			movePos.x = 0;
		}
	}

	//	�d�͂����W�ɉ��Z����
	setPosition(getPosition().x, getPosition().y + Gy);

	//	�f�o�b�O�pBox�̍��W�ݒ�
#ifdef _DEBUG
	box->setTextureRect(cocos2d::Rect(getPosition().x, getPosition().y, getContentSize().width, getContentSize().height));
	box->setPosition(getPosition());
#endif // _DEBUG

}

int Character::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer)
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
