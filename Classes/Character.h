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
	DIR_MAX
};

class Character
	:public cocos2d::Sprite
{
public:
	Character();
	virtual ~Character();
	virtual void update(float d) = 0;

	void SetInit(std::string ImagePass,DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene);

	void MoveAction();
	//	アニメーションのステートのGetSet
	AnimState GetState();
	void SetState(AnimState st);
	//	向きのGetSet
	DIR GetDir();
	void SetDir(DIR dir);
	//	スピードのGetSet
	void SetSpeed(int sp);
	int GetSpeed();

	void SetMoveFlag(bool flag);
	//	移動方向のGetSet
	void SetMovePosX(float pos);
	void SetMovePosY(float pos);

protected:
	float Gy;								//	重力用

	OprtState *_oprtState;

	AnimState state;
	AnimState oldState;
	int speed;
	bool moveFlag;
	cocos2d::Vec2 movePos;					//	指を離すまで移動するための移動方向
	cocos2d::Vec2 colMovePos;				//	当たり判定を付与した最終的なmovePos

	DIR charaDir;
	DIR startDir;
	DIR OldDir;
};

