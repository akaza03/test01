#pragma once
#include <functional>
#include "ActSet.h"
#include "AnimManager.h"
#include "OprtState.h"

class OprtState;

//using spPointer = bool (*)(cocos2d::Sprite);
using actionPoint = std::function<bool(cocos2d::Sprite&,struct CharaID&)>;

//	キャラクターの情報用
struct CharaID
{
	cocos2d::Vec2 speed;													//	移動スピード
	cocos2d::EventKeyboard::KeyCode key;									//	どのキーを押したら処理するのか(List)
	AnimState anim;															//	現在のアニメーション
	cocos2d::Point checkPoint;												//	当たり判定用
	CharaType cType;														//	キャラクターのタイプ
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

	AnimState GetState();															//	アニメーションのステートのGetSet
	void SetState(AnimState st);
	
	DIR GetDir();																	//	キャラクターの向きのGetSet
	void SetDir(DIR dir);
	
	int GetSpeed();																	//	スピードのGetSet
	void SetSpeed(int sp);

	bool GetMoveFlagX();															//	X座標を移動中かどうかのGetSet
	void SetMoveFlagX(bool flag);

	bool GetMoveFlagY();															//	Y座標を移動中かどうかのGetSet
	void SetMoveFlagY(bool flag);

	cocos2d::Vec2 GetMovePos();														//	移動方向のGetSet
	void SetMovePosX(float pos);
	void SetMovePosY(float pos);

	void SetJumpStart(bool flag);													//	ジャンプ開始時のSet

	CharaType GetCharaType();														//	キャラのタイプのGet

	void SetDBBox(Sprite* sp);														//	デバッグ時の当たり判定用BoxのSet

protected:
	void CheckCol();																//	衝突判定用(updateで呼び出す)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	代入した座標のタイルを返す

	void dirUpdate();																//	向きの更新
	void moveUpdate();																//	移動の更新
	void AnimStateUpdate();															//	アニメーションの更新

	Sprite *_box;																	//	当たり判定用のBOX
	float _Gravity;																	//	重力
	cocos2d::Vec2 _oldPos;															//	1フレーム前の座標
	OprtState *_oprtState;															//	操作制御
	AnimState _state;																//	現在のアニメーション
	AnimState _oldState;															//	1フレーム前のアニメーション

	bool _moveFlagX;																//	キャラクターがX座標を移動中かどうか
	bool _moveFlagY;																//	キャラクターがY座標を移動中がどうか
	bool _JumpStart;																//	ジャンプ開始時のフラグ

	cocos2d::Vec2 _movePos;															//	移動時に現在の座標に加算する
	int _speed;																		//	移動スピード

	DIR _charaDir;																	//	キャラクターの向き
	DIR _startDir;																	//	ゲーム開始時の向き
	DIR _oldDir;																	//	1フレーム前の向き

	CharaType _cType;																//	キャラクターのタイプ



	CharaID _charaID;														//	キャラクターの情報用
	std::map<const char *,CharaID> _charaList;								//	キャラクターの情報用リスト
	std::list<cocos2d::EventKeyboard::KeyCode> _keyList;					//	キー用のリスト

	std::list<actionPoint> _actList;										//	アクションの管理用

	actionPoint _act;

	//bool(*_act)(cocos2d::Sprite&);
};
