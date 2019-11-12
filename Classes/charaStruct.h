#pragma once

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

//	使用キー
enum UseKey
{
	K_NON,
	K_LEFT,
	K_RIGHT,
	K_UP,
	K_DOWN,
	KEY_MAX
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
