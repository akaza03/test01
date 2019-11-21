/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
	//	�摜�̓ǂݍ���
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ImageList.plist");


    //////////////////////////////
    // 1. super init first
    if (!Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("GameScene", "fonts/Marker Felt.ttf", 24);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }
	

	//	���C���[�̍쐬
	BGLayer = Layer::create();
	this->addChild(BGLayer,LayerNumber::BG, "BGLayer");
	CharaLayer = Layer::create();
	this->addChild(CharaLayer,LayerNumber::CHARA, "CharaLayer");

	//	�}�b�v�̓ǂݍ���
	TMXTiledMap* tiledMap = TMXTiledMap::create("map.tmx");
	BGLayer->addChild(tiledMap,1,"stageMap");

	//TMXLayer* layer = tiledMap->getLayer("layer1");
	//layer->setGlobalZOrder(1);
	//layer = tiledMap->getLayer("layer2");
	//layer->setGlobalZOrder(2);

	//	�w�i�摜���܂Ƃ߂ĕ\������p
	auto spNode = SpriteBatchNode::create("image/Environment/background.png");
	BGLayer->addChild(spNode, 0);
	for (int i = 0; i <= 2; i++)
	{
		auto BGSP = Sprite::createWithTexture(spNode->getTexture());
		//	�A���J�[�|�C���g��^�񒆂��獶���ɕύX
		BGSP->setAnchorPoint(Vec2(0, 0));
		BGSP->setPosition(Vec2(BGSP->getContentSize().width * i, 0));
		spNode->addChild(BGSP);
	}
	
	//	�v���C���[�̍쐬
	auto player = Player::create();

	//	playerLayer��ǂݍ��݁A�v���C���[�̍��W�����肷��
	TMXLayer* layer = tiledMap->getLayer("player");
	//	�v���C���[�̍��W
	cocos2d::Vec2 Ppos = cocos2d::Vec2(0, 0);
	for (int y = 0; y < layer->getLayerSize().height;y++)
	{
		for (int x = 0; x < layer->getLayerSize().width; x++)
		{
			if (layer->getTileGIDAt(cocos2d::Vec2(x,y)) != 0)
			{
				Ppos = cocos2d::Vec2(x * layer->getMapTileSize().width, y * layer->getMapTileSize().height);
				layer->removeFromParentAndCleanup(true);
			}
		}
	}

	player->SetInit("image/Sprites/player/player-idle/player-idle-1.png", DIR::RIGHT, Ppos, Vec2(5,6), this);
	CharaLayer->addChild(player, 0);

#ifdef _DEBUG
	//	�f�o�b�O�p���C���[�̍쐬
	DBLayer = Layer::create();
	this->addChild(DBLayer, LayerNumber::DB, "DBLayer");

	//	�f�o�b�O�pBox������ăv���C���[�ɓn��
	auto DBBox = Sprite::create();
	//DBBox->setColor(Color3B(0, 255, 128));
	DBBox->setOpacity(128);
	DBLayer->addChild(DBBox,1,"DBBox");
	player->SetDBBox(DBBox);
#endif // _DEBUG
    
	this->scheduleUpdate();
	return true;
}

void GameScene::update(float d)
{
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
