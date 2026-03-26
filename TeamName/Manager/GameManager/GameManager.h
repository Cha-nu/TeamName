#pragma once

#include <iostream>
#include <string>

// 전방 선언 (순환 참조 방지 및 컴파일 속도 향상)
class SceneManager;
class Player;

class GameManager
{
private:
	bool DebugKey = false; // 디버그용 
    bool IsRunning;      // 게임 실행 루프 제어 플래그
    SceneManager* m_pSceneManager;
    Player* m_pPlayer;

public:
    GameManager();
    ~GameManager();

    // 게임 시작 전 초기화 (클래스 생성)
    bool Init();

    // 메인 게임 루프 (TeamName.cpp에서 호출)
    void Run();

    // 시스템 로직 업데이트
    void Update();

    // 화면 출력 관리
    void Render();

	// 현재 상태 변경
	void Exit();

    // 메모리 해제 및 종료 처리
    void Release();

	// 플레이어 생서
	void CreatePlayer();

    // 게임 종료 플래그 설정
    void SetRunning(bool isRunning) { IsRunning = isRunning; }
};
