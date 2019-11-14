#pragma once

//	�g�p�L�[
enum class UseKey
{
	K_NON,
	K_LEFT,
	K_RIGHT,
	K_UP,
	K_DOWN,
	K_MAX
};

UseKey begin(UseKey);
UseKey end(UseKey);
UseKey operator*(UseKey key);
UseKey operator++(UseKey& key);


