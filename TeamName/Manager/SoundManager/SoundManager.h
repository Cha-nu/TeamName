#pragma once
#include <windows.h>
#include <mmsystem.h>
#include <string>

#pragma comment(lib, "winmm.lib")

// 사운드 매니저 싱글톤 클래스 입니다.
// 사용 방법은 "Music/파일의이름.mp3"
// Music폴더안에 mp3파일만 넣고 사용해주시면 됩니다.

class SoundManager
{
public:
	static SoundManager& GetInstance(){
		static SoundManager instance;
		return instance;
	}
	
	// 배경음악 재생(무한 반복)
	void PlayBGM(const std::string& filename);
	
	// 효과음 재생(한 번만 입니다.)
	void PlayEffectSound(const std::string& filename);
	
	// 모든 사운드 정지
	void StopAll();
	
private:
	SoundManager() {}
	~SoundManager() {StopAll(); }
	
};
