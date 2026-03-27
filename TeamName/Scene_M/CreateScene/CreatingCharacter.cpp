// 캐릭터 생성 화면.cpp

#include "CreatingCharacter.h"
#include "../../Player/Player.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene/MainScene.h" // 씬 전환을 위해 추가

#include <iostream>
#include <string>
#include <cstdlib> // system의 cls, pause 사용하기 위해 추가
#include <windows.h> // [0327 추가] 좌표 이동(gotoxy) 사용을 위해 추가

#include "Manager/GameManager/GameManager.h"

// [0327 추가] 지정한 X, Y 좌표로 콘솔 커서를 이동시키는 함수
void Create_gotoxy(int x , int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}

// 초기화 함수(1회 실행)
void CharacterChoice::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성

	// 콘솔 깨끗히 지우기
	system("cls");
	// 버퍼에 남은 문자 제거
	std::cin.clear();
}

// 화면 출력
void CharacterChoice::Render() {
	// 아스키 아트 중앙 배치
	Create_gotoxy(32 , 2);  std::cout << "                   ,:$@@@@*~                      ";
	Create_gotoxy(32 , 3);  std::cout << "                 .*@@@@@@@@@@;                    ";
	Create_gotoxy(32 , 4);  std::cout << "                -@@@@@===$@@@@#.                  ";
	Create_gotoxy(32 , 5);  std::cout << "               ~@@@@$     .#@@@@.                 ";
	Create_gotoxy(32 , 6);  std::cout << "              ,@@@@#        @@@@#                 ";
	Create_gotoxy(32 , 7);  std::cout << "              $@@@@~   ,.   !@@@@!                ";
	Create_gotoxy(32 , 8);  std::cout << "             :@@@@@   *@@:   @@@@@.               ";
	Create_gotoxy(32 , 9);  std::cout << "             =@@@@@   @@@@   @@@@@!               ";
	Create_gotoxy(32 , 10); std::cout << "             @@@@@@@!@@@@~  .@@@@@$               ";
	Create_gotoxy(32 , 11); std::cout << "            .@@@@@@@@@@@$   =@@@@@@               ";
	Create_gotoxy(32 , 12); std::cout << "            :@@@@@@@@@@#    @@@@@@@               ";
	Create_gotoxy(32 , 13); std::cout << "            :@@@@@@@@@#    #@@@@@@@               ";
	Create_gotoxy(32 , 14); std::cout << "            ,@@@@@@@@@*   #@@@@@@@@               ";
	Create_gotoxy(32 , 15); std::cout << "             @@@@@@@@@.  -@@@@@@@@$               ";
	Create_gotoxy(32 , 16); std::cout << "             $@@@@@@@@=  #@@@@@@@@!               ";
	Create_gotoxy(32 , 17); std::cout << "             !@@@@@@@@@##@@@@@@@@@,               ";
	Create_gotoxy(32 , 18); std::cout << "              #@@@@@@@@;!@@@@@@@@*                ";
	Create_gotoxy(32 , 19); std::cout << "              ~@@@@@@@,  ;@@@@@@@.                ";
	Create_gotoxy(32 , 20); std::cout << "               !@@@@@@    @@@@@@-                 ";
	Create_gotoxy(32 , 21); std::cout << "                !@@@@@;  $@@@@@-                  ";
	Create_gotoxy(32 , 22); std::cout << "                 ~#@@@@@@@@@@=.                   ";
	Create_gotoxy(32 , 23); std::cout << "                   ;#@@@@@@=~                     ";

	// UI 텍스트 중앙 배치
	Create_gotoxy(25 , 25); std::cout << "============================================================";
	Create_gotoxy(25 , 26); std::cout << "                당신의 캐릭터를 생성하세요...                ";
	Create_gotoxy(25 , 27); std::cout << "============================================================";
}

// 입력 및 로직 처리
void CharacterChoice::Update() {
	std::string name; // 플레이어 닉네임 변수 선언

	std::cin.ignore(INT_MAX , '\n');
	// 플레이어 이름 입력 받기 (위치는 중앙으로 설정)
	Create_gotoxy(40, 29);  std::cout << ">> 닉네임을 입력하세요: ";
	std::cin >> name;

	// 입력받은 이름 전달
	// Player newPlayer(name);
	GameManager::getInstance().SetPlayer(name); // GameManager용 플레이어 정보 설정

	// 입력 받은 정보 출력
	system("cls"); // 결과창을 위해 클리어
	Create_gotoxy(30 , 5); std::cout << "============================================================";
	Create_gotoxy(30 , 6); std::cout << "                  캐릭터 생성이 완료되었습니다.                 ";
	Create_gotoxy(30 , 7); std::cout << "============================================================";
	Create_gotoxy(50 , 9);  std::cout << " [ 닉네임 ]   : " << GameManager::getInstance().GetPlayer()->Getstat().name;  // GameManager용 출력
	Create_gotoxy(50 , 10); std::cout << " [ Lv ]       : " << GameManager::getInstance().GetPlayer()->Getstat().Level;
	Create_gotoxy(50 , 11); std::cout << " [ 체력 ]     : " << GameManager::getInstance().GetPlayer()->Getstat().HP;
	Create_gotoxy(50 , 12); std::cout << " [ 스테미나 ] : " << GameManager::getInstance().GetPlayer()->Getstat().Stamina;
	Create_gotoxy(50 , 13); std::cout << " [ 공격력 ]   : " << GameManager::getInstance().GetPlayer()->Getstat().Atk_Damage;
	Create_gotoxy(50 , 14); std::cout << " [ EXP ]      : " << GameManager::getInstance().GetPlayer()->Getstat().EXP;
	Create_gotoxy(30 , 16); std::cout << "============================================================";

	Create_gotoxy(30 , 18); system("pause"); // 잠시 멈추기(사용자에게 메시지 보여주기 위해 작성)

	// SceneManager를 통해 다음 씬으로 전환
	SceneManager::getInstance().Replace_Scene(new MainScene());
	return; // 씬이 교체되었으므로 Update 종료
}

// 종료 함수
void CharacterChoice::Exit() {
	// 씬을 나갈 때 메모리 해제 등의 필요한 부분이 있다면 작성
}