#pragma once

#include <string>
#include <queue>

// 전방 선언
class SceneManager;
class Player;
class Monster;

class GameManager
{
private:
    bool DebugKey = false; // 디버그용 
    bool IsRunning;      // 게임 실행 루프 제어 플래그
	Player* Character;

    // 단계별 몬스터 큐
	std::queue<Monster*> MonsterQueue; 

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
	Player* GetPlayer();

	// 몬스터 
	Monster* ManageMonster();

    // 게임 종료 플래그 설정
    void SetRunning(bool isRunning) { IsRunning = isRunning; }
};
