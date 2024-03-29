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

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <memory>
#include <Effekseer/Effekseer.h>

enum LayerNumber
{
	BG,						//	バックグラウンド用レイヤー
	CHARA,					//	キャラクター用レイヤー
	FG,						//	フロントグラウンド用レイヤー
	DB,						//	デバッグ用レイヤー
	LAYER_MAX
};

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

private:
	cocos2d::Layer * BGLayer;				//	バックグラウンド用レイヤー
	cocos2d::Layer * CharaLayer;			//	キャラクター用レイヤー
	cocos2d::Layer * FGLayer;				//	フロントグラウンド用レイヤー
	cocos2d::Layer * DBLayer;				//	デバッグ用レイヤー

	void update(float d);

	std::unique_ptr<efk::EffectManager> effectMng;
	void visit(cocos2d::Renderer *renderer, const cocos2d::Mat4& parentTransform, uint32_t parentFlags)
	{
		effectMng->begin(renderer, _globalZOrder);
		cocos2d::Scene::visit(renderer, parentTransform, parentFlags);
		effectMng->end(renderer, _globalZOrder);
	}

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);
};

#endif // __GAME_SCENE_H__
