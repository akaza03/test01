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
	ENEMY1,
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

	void MoveAction();
	
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
	Sprite *box;
	void CheckCol();																//	衝突判定用(updateで呼び出す)
	int GetTile(cocos2d::Vec2 _pos, cocos2d::TMXLayer *_layer);						//	代入した座標のタイルを返す

	float Gy;																		//	重力用

	OprtState *_oprtState;

	AnimState state;
	AnimState oldState;
	int speed;
	bool moveFlagX;																	//	キャラクターがX座標を移動中かどうか
	bool moveFlagY;																	//	キャラクターがY座標を移動中がどうか
	bool JumpStart;																	//	ジャンプ開始時のフラグ
	cocos2d::Vec2 movePos;															//	指を離すまで移動するための移動方向

	DIR charaDir;
	DIR startDir;
	DIR OldDir;

	
	std::map<spPointer, spPointer> act;												//	アクションの管理用
};

