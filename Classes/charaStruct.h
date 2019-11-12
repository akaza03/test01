#pragma once

//	�A�j���[�V�����̃^�C�v
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

//	�L�����N�^�[�̃^�C�v
enum CharaType
{
	PLAYER,
	ENEMY,
	CHARA_MAX
};

//	�g�p�L�[
enum UseKey
{
	K_NON,
	K_LEFT,
	K_RIGHT,
	K_UP,
	K_DOWN,
	KEY_MAX
};

//	����
enum DIR
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	DIR_MAX
};
