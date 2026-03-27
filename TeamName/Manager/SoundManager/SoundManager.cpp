#include "SoundManager.h"

void SoundManager::PlayBGM(const std::string& filename){
	
	// 기존 BGM이 틀어져있다면 끄고 새로운걸로 플레이 합니다.
	mciSendString(TEXT("close bgm"), NULL, 0, NULL);
	
	std::string command = "open \"" + filename + "\" type mpegvideo alias bgm";
	mciSendStringA(command.c_str(), NULL, 0, NULL);
	mciSendString(TEXT("play bgm repeat"), NULL, 0, NULL);
	
}

void SoundManager::PlayEffectSound(const std::string& filename){
	
	// BGM이 아닌 간단한 이펙트를 재생하고 싶을때 사용하시면 됩니다.
	mciSendString(TEXT("close effect"),NULL, 0, NULL);
	
	std::string command = "open \"" + filename + "\" type mpegvideo alias effect";
	mciSendStringA(command.c_str(), NULL, 0, NULL);
	mciSendString(TEXT("play effect from 0"),NULL, 0, NULL);
	
}

void SoundManager::StopAll(){
	// 소멸자에서 현재 틀어져있는 모든 BGM,Effect 재생멈춤
	mciSendString(TEXT("stop bgm"), NULL, 0, NULL);
	mciSendString(TEXT("close bgm"), NULL, 0, NULL);
	mciSendString(TEXT("stop effect"), NULL, 0, NULL);
	mciSendString(TEXT("close effect"), NULL, 0, NULL);
}
