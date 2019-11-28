#pragma once
#include <memory>
#include <cocos2d.h>

#define lpAudioManager AudioManager::GetInstance()

class AudioManager
{
public:
	static AudioManager& GetInstance()
	{
		if (s_Instance == nullptr)
		{
			s_Instance = new AudioManager();
		}
		return *s_Instance;
	}
	~AudioManager();

	void update();

	void SetBank(const char* pass, const char* name);	//	�I���������Đ�
	void SetStream(const char* pass);					//	�X�g���[�~���O�Đ�
private:
	AudioManager();
	static AudioManager* s_Instance;
};

