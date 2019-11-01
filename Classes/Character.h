#pragma once
#include "cocos2d.h"
#include "AnimManager.h"
#include "OprtState.h"

class OprtState;

//	アニメーションのタイプ
enum AnimState
{
	IDLE,
	RUN,
	RSHOT,
	SHOTUP,
	STAND,
	JUMP,
	CLING,
	DUCK,
	HURT,
	STATE_MAX
};

//	キャラクターのタイプ
enum CharaType
{
	PLAYER,
	ENEMY,
	CHARA_MAX
};

//	向き
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DIR_MAX
};

using spPointer = bool (*)(cocos2d::Sprite);


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

protected:
	void CheckCol();																//	衝突判定用(updateで呼び出す)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	代入した座標のタイルを返す

	void moveUpdate();																//	移動の更新
	void dirUpdate();																//	向きの更新

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

	DIR _charaDir;
	DIR _startDir;
	DIR _oldDir;

	
	std::map<spPointer, spPointer> act;												//	アクションの管理用
};
