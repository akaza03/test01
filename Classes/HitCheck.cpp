#include "Character.h"
#include "_DebugConOut.h"
#include "HitCheck.h"


bool HitCheck::operator()(cocos2d::Sprite & sp, ActData &act)
{
	//	�Փ˗p�̃��C���[�̎擾
	auto director = cocos2d::Director::getInstance();
	auto map = (cocos2d::TMXTiledMap*)director->getRunningScene()->getChildByName("BGLayer")->getChildByName("stageMap");
	auto layerMap = map->getLayer("collision");

	//	�v���C���[�̍��W
	auto pos = cocos2d::Vec2(sp.getPosition().x, layerMap->getLayerSize().height * layerMap->getMapTileSize().height - sp.getPosition().y);
	//	�w�肳�ꂽ�ꏊ�̃^�C��ID
	int tile = 0;

	//	�}�b�v�Ƃ̓����蔻��
	//	��
	auto DownPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height + 1);
	tile = GetTile(DownPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		act.checkPoint[DIR::DOWN] = true;
	}
	else
	{
		act.checkPoint[DIR::DOWN] = false;
	}

	//	��
	auto UpPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width, pos.y / layerMap->getMapTileSize().height - 1);
	tile = GetTile(UpPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		act.checkPoint[DIR::UP] = true;
	}
	else
	{
		act.checkPoint[DIR::UP] = false;
	}

	// ��
	auto LPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width - 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(LPos, layerMap);
	if (tile != 0)
	{
		TRACE("��%d", tile);
		act.checkPoint[DIR::LEFT] = true;
	}
	else
	{
		act.checkPoint[DIR::LEFT] = false;
	}

	//	�E
	auto RPos = cocos2d::Vec2(pos.x / layerMap->getMapTileSize().width + 1, pos.y / layerMap->getMapTileSize().height);
	tile = GetTile(RPos, layerMap);
	if (tile != 0)
	{
		TRACE("�E%d", tile);
		act.checkPoint[DIR::RIGHT] = true;
	}
	else
	{
		act.checkPoint[DIR::RIGHT] = false;
	}
	
	return false;
}

int HitCheck::GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer * _layer)
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
