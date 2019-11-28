#include "ck/ck.h"
#include "ck/config.h"
#include "ck/bank.h"
#include "ck/sound.h"
#include "AudioManager.h"

AudioManager* AudioManager::s_Instance = nullptr;

AudioManager::AudioManager()
{
#if CK_PLATFORM_ANDROID
	CkConfig config(env, activity);
#else
	CkConfig config;
#endif;
	CkInit(&config);
}


AudioManager::~AudioManager()
{
	CkShutdown();
}

void AudioManager::update()
{
	CkUpdate();
}

void AudioManager::SetBank(const char* pass, const char* name)
{
	//	ckb�t�@�C���̎w��
	CkBank* bank = CkBank::newBank(pass);
	//	�Đ����������̖��O���w��
	CkSound* sound = CkSound::newBankSound(bank, name);
	sound->play();
}

void AudioManager::SetStream(const char* pass)
{
	CkSound* _music = CkSound::newStreamSound(pass);
	_music->setLoopCount(-1);
	_music->play();
}
