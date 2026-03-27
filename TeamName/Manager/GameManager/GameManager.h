#pragma once

#include <string>

// 전방 선언 (순환 참조 방지 및 컴파일 속도 향상)
class SceneManager;
class Player;

class GameManager
{
private:
    bool DebugKey = false; // 디버그용 
    bool IsRunning;      // 게임 실행 루프 제어 플래그
	Player* Character;

    // 싱글톤
    GameManager();
    ~GameManager();

    GameManager(const GameManager&) = delete;
    GameManager& operator=(const GameManager&) = delete;

public:
    // 인스턴스 반환 정적 메서드
    static GameManager& getInstance()
    {
        static GameManager instance;
        return instance;
    }

    // 게임 시작 전 초기화 (클래스 생성)
    bool Init();

    // 메인 게임 루프 
    void Run();

    // 시스템 로직 업데이트
    void Update();

    // 화면 출력 관리
    void Render();

    // 현재 상태 변경
    void Exit();

    // 메모리 해제 및 종료 처리
    void Release();

    // 플레이어
	void SetPlayer(std::string& name);
	Player& GetPlayer(); // 읽기 전용 이여야 하는데, 일단 참조 반환으로 수정했습니다. (const Player& GetPlayer() const;)

    // 게임 종료 플래그 설정
    void SetRunning(bool isRunning) { IsRunning = isRunning; }
};
