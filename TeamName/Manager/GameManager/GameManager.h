#pragma once

#include <string>
#include <vector>

// 전방 선언
class SceneManager;
class Player;
class Monster;

class GameManager
{
private:
    bool DebugKey = true; // 디버그용 
    bool IsRunning;      // 게임 실행 루프 제어 플래그
	Player* Character;

	// 0. 수능(튜토리얼보스) / 1. c언어(normal) / 2. c++(normal) / 3. graphics(normal) / 4. unreal(normal) / 5. 취업(최종보스)
	std::vector<std::string> MonsterName = {"c언어", "c++", "graphics", "unreal"}; // 몬스터 이름 리스트

	Monster* CurrentMonster; // 현재 스테이지의 몬스터를 가리키는 포인터

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
	Monster* GetMonster() const;

	// 매 스테이지마다 몬스터 생성 및 큐에 추가
	bool CreateMonster();

    // 게임 종료 플래그 설정
    void SetRunning(bool isRunning) { IsRunning = isRunning; }
};
