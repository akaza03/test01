#pragma once
#include <functional>
#include "ActSet.h"
#include "AnimManager.h"
#include "UseKey.h"
#include "OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct ActData&)>;
using keyList = std::map<UseKey, std::pair<bool, bool>>;							//	キー用のリスト(押されているかの判定,登録されているかの判定)
using hitList = std::map<DIR, bool>;												//	当たり判定用リスト

//	キャラクターの情報用
struct ActData
{
	int speed;																		//	移動スピード
	keyList key;																	//	どのキーを押したら処理するのか(List)
	AnimState anim;																	//	再生するアニメーション
	hitList checkPoint;																//	当たり判定用
	//cocos2d::Point checkPoint;
	CharaType cType;																//	キャラクターのタイプ
	//	次に呼ぶ関数
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass,DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene);

	void SetDBBox(Sprite* sp);														//	デバッグ時の当たり判定用BoxのSet

private:
	void InitActData(int speed);													//	ActDataの初期化

protected:
	Sprite *_box;																	//	当たり判定用のBOX
	float _Gravity;																	//	重力
	OprtState *_oprtState;															//	操作制御
	AnimState _state;																//	現在のアニメーション
	AnimState _oldState;															//	1フレーム前のアニメーション
	ActData _actData;																//	キャラクターの情報用
	std::map<const char *,ActData> _charaList;										//	キャラクターの情報用リスト

	//std::list<cocos2d::EventKeyboard::KeyCode> _keyList;							//	キー用のリスト

	//std::list<actionPoint> _actList;												//	アクションの管理用

	//bool(*_act)(cocos2d::Sprite&, ActData &);										//	関数ポインタ
};
