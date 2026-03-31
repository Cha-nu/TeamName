// 캐릭터 생성 화면.cpp

#include "CreatingCharacter.h"
<<<<<<< HEAD
#include "Player.h"
=======
#include "../../Player/Player.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene/MainScene.h" // 씬 전환을 위해 추가
>>>>>>> update

#include <iostream>
#include <string>
#include <cstdlib> // system의 cls, pause 사용하기 위해 추가
<<<<<<< HEAD
=======
#include <windows.h> // [0327 추가] 좌표 이동(gotoxy) 사용을 위해 추가

#include "Manager/GameManager/GameManager.h"

// [0327 추가] 지정한 X, Y 좌표로 콘솔 커서를 이동시키는 함수
void Create_gotoxy(int x , int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , pos);
}
>>>>>>> update

// 화면 중앙 좌표를 구해오는 함수
void GetCreateScreenCenterXY(int& centerX, int& centerY) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	centerX = width / 2;
	centerY = height / 2;
}

// 초기화 함수(1회 실행)
void CharacterChoice::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성
<<<<<<< HEAD
=======

	// 콘솔 깨끗히 지우기
	system("cls");
<<<<<<< HEAD
>>>>>>> update
=======
	// 버퍼에 남은 문자 제거
	std::cin.clear();
>>>>>>> update
}

// 화면 출력
void CharacterChoice::Render() {
<<<<<<< HEAD
<<<<<<< HEAD
	// 콘솔 깨끗히 지우기
	system("cls");

	// 아스키 아트
	std::string CharacterCreate = R"(
           << 캐릭터 생성 >>
----,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
---,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
---,,,,,,,,,,,,~!*****;-,,,,,,,,,,,,,,,,
--,,,,,,,,,,,,!********=;,,,,,,,,,,,,,,,
--,,,,,,,,,,,!*!******===!,,,,,,,,,,,,,,
----,,,,,,,,,********===$$,,,,,,,,,,,,,,
-,,--,,,,,,,:=******===$$$,,,,,,,,,,,,,,
----,,,,,,,,:****====$$$$$~,,,,,,,,,,,,,
-,-,,,,,,,,,:==*====$$$$$$;,,,,,,,,,,,,,
---,,-,,,,,,:=*====$$$$$$$;,,,,,,,,,,,,,
---,,,,-,,,,:======$$$#$$$;,,,,,,,,,,,,,
--,-,,,,,--,:***=$$=$$####*,,,,,,,,,,,,,
---,,,,,,=#;:!!**=$$#$$===:;*$,,,,,,,,,,
---,--,,,,!$$$===********$$$$,,,,,,,,,,,
------,,,,,,:!==*!!;;;!**$:-,,,,,,,,,,,,
------,-,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
-------,,,,,,,,,,.    ,,,,,,,,,,,,,,,,,,
------,,,,,,,,,,       .,,,,,,,,,,,,,,,,
-----,--,,,,,,,,   ..   ,,,,,,,,,,,,,,,,
-----,,,,,,,,,,,  .,,   ,,,,,,,,,,,,,,,,
---,,-,,,,,,,,,,,,,,,   ,,,,,,,,,,,,,,,,
-------,,,,,,,,,,,,    .,,,,,,,,,,,,,,,,
------,,,,,,,,,,,,.   ,,,,,,,,,,,,,,,,,,
------,,,,,,,,,,,,   ,,,,,,,,,,,,,,,,,,,
------,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
------,,,,,,,,,,,,   ,,,,,,,,,,,,,,,,,,,
------,,,,,,,,,,,,   ,,,,,,,,,,,,,,,,,,,
---,--,-,,,,,,,,,,.  ,,,,,,,,,,,,,,,,,,,
-------,--,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
----------,,,,,-,,,,,,,,,,,,,,,,,,,,,,,,
-------,-,,,,-,,..       ;,,,,,,,,,,,,,,
-------,,-,,-= ,..      .*!,,,,,,,,,,,,,
-----------:*=,   .    ..*=*-,,,,,,,,,,,
----------****!   .;    .====;,,,,,,,,,,
-------;*******   ;;;   ~***==*!,,,,,,,,
-----**********  .:;*   !**==*=***-,,,,,
--!*******=****- -,*~. .****=**=****;,,,
~*********=**==*  :;!  ~**=====*******:,
*!********=**=**. :;;. !*=**=*=*=*****=*
************==**. ;;;- ***======**=*****
****=**=****==**!-:;!;~*===*=*=*==*==***
*=************=*=~;;;!**=*======*===**==
*=*****=**=****==;;;;!**===*======*==*=*
*=******===***=*==;:;**==*===*======*==*
*=********==***===;;!**==*=======*======
*==**=*=======*=*=!;***=**====*=========
**=****=*====**====;**==*====*==========
*==*=**=======*====*=*==*===============
===***========**==============*=========
)";

	std::cout << CharacterCreate << "\n"; // 아스키 아트 출력
	std::cout << "============================================================\n";
	std::cout << "                당신의 캐릭터를 생성하세요...                  \n";
	std::cout << "============================================================\n";
=======
=======
	int cx, cy;
	GetCreateScreenCenterXY(cx, cy);

	int artX = cx - 23; // 기존 중앙(60) 대비 32 위치였으므로 -28 
	int artStartY = cy - 20; // 기존 세로(15) 대비 2 위치였으므로 -13

>>>>>>> update
	// 아스키 아트 중앙 배치
	Create_gotoxy(artX , artStartY);      std::cout << "                   ,:$@@@@*~                      ";
	Create_gotoxy(artX , artStartY + 1);  std::cout << "                 .*@@@@@@@@@@;                    ";
	Create_gotoxy(artX , artStartY + 2);  std::cout << "                -@@@@@===$@@@@#.                  ";
	Create_gotoxy(artX , artStartY + 3);  std::cout << "               ~@@@@$     .#@@@@.                 ";
	Create_gotoxy(artX , artStartY + 4);  std::cout << "              ,@@@@#        @@@@#                 ";
	Create_gotoxy(artX , artStartY + 5);  std::cout << "              $@@@@~   ,.   !@@@@!                ";
	Create_gotoxy(artX , artStartY + 6);  std::cout << "             :@@@@@   *@@:   @@@@@.               ";
	Create_gotoxy(artX , artStartY + 7);  std::cout << "             =@@@@@   @@@@   @@@@@!               ";
	Create_gotoxy(artX , artStartY + 8);  std::cout << "             @@@@@@@!@@@@~  .@@@@@$               ";
	Create_gotoxy(artX , artStartY + 9);  std::cout << "            .@@@@@@@@@@@$   =@@@@@@               ";
	Create_gotoxy(artX , artStartY + 10); std::cout << "            :@@@@@@@@@@#    @@@@@@@               ";
	Create_gotoxy(artX , artStartY + 11); std::cout << "            :@@@@@@@@@#    #@@@@@@@               ";
	Create_gotoxy(artX , artStartY + 12); std::cout << "            ,@@@@@@@@@*   #@@@@@@@@               ";
	Create_gotoxy(artX , artStartY + 13); std::cout << "             @@@@@@@@@.  -@@@@@@@@$               ";
	Create_gotoxy(artX , artStartY + 14); std::cout << "             $@@@@@@@@=  #@@@@@@@@!               ";
	Create_gotoxy(artX , artStartY + 15); std::cout << "             !@@@@@@@@@##@@@@@@@@@,               ";
	Create_gotoxy(artX , artStartY + 16); std::cout << "              #@@@@@@@@;!@@@@@@@@*                ";
	Create_gotoxy(artX , artStartY + 17); std::cout << "              ~@@@@@@@,  ;@@@@@@@.                ";
	Create_gotoxy(artX , artStartY + 18); std::cout << "               !@@@@@@    @@@@@@-                 ";
	Create_gotoxy(artX , artStartY + 19); std::cout << "                !@@@@@;  $@@@@@-                  ";
	Create_gotoxy(artX , artStartY + 20); std::cout << "                 ~#@@@@@@@@@@=.                   ";
	Create_gotoxy(artX , artStartY + 21); std::cout << "                   ;#@@@@@@=~                     ";

	// UI 텍스트 중앙 배치
<<<<<<< HEAD
	Create_gotoxy(25 , 25); std::cout << "============================================================";
	Create_gotoxy(25 , 26); std::cout << "                당신의 캐릭터를 생성하세요...                ";
	Create_gotoxy(25 , 27); std::cout << "============================================================";
>>>>>>> update
=======
	int uiX = cx - 30; // 60 기준 25 위치
	int uiY = cy + 5; // 15 기준 25 위치
	Create_gotoxy(uiX , uiY);     std::cout << "============================================================";
	Create_gotoxy(uiX , uiY + 1); std::cout << "                당신의 캐릭터를 생성하세요...                ";
	Create_gotoxy(uiX , uiY + 2); std::cout << "============================================================";
>>>>>>> update
}

// 입력 및 로직 처리
void CharacterChoice::Update() {
<<<<<<< HEAD
	Player newPlayer;

	std::string name; // 플레이어 닉네임
	int hp , stamina , atk; // 체력, 스테미나, 공격

	// 플레이어 이름 입력 받기
	std::cout << "\n >> 닉네임을 입력하세요: ";
	std::cin >> name;

	// 플레이어 스탯(HP, Stamina, Atk_Damage) 입력
	std::cout << "\n >> 플레이어의 체력을 입력하세요: ";
	std::cin >> hp;

	std::cout << "\n >> 플레이어의 스테미나를 입력하세요: ";
	std::cin >> stamina;

	std::cout << "\n >> 플레이어의 공격력을 입력하세요: ";
	std::cin >> atk;

	// 입력받은 값으로 스탯 초기화
	newPlayer.InitializeStat(hp , name , atk , stamina);

	// 입력 받은 정보 출력
	std::cout << "============================================================\n";
	std::cout << "                  캐릭터 생성이 완료되었습니다.                 \n";
	std::cout << "============================================================\n";
	std::cout << " [ 닉네임 ] : " << newPlayer.Getstat().name << "\n";
	std::cout << " [ 레벨 ] : " << newPlayer.Getstat().Level << "\n";
	std::cout << " [ 체력 ] : " << newPlayer.Getstat().HP << "\n";
	std::cout << " [ 스테미나 ] : " << newPlayer.Getstat().Stamina << "\n";
	std::cout << " [ 공격력 ] : " << newPlayer.Getstat().Atk_Damage << "\n";
	std::cout << " [ 경험치 ] : " << newPlayer.Getstat().EXP << "\n";
	std::cout << "============================================================\n";

	system("pause"); // 잠시 멈추기(사용자에게 메시지 보여주기 위해 작성)

	// SceneManager를 통해 다음 씬으로 전환

=======
	std::string name; // 플레이어 닉네임 변수 선언

	int cx, cy;
	GetCreateScreenCenterXY(cx, cy);

	// OS 버퍼에 쌓인 모든 입력 강제 소각
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	std::cin.clear();

	// 플레이어 이름 입력 받기 (위치는 중앙으로 설정)
	Create_gotoxy(cx - 30, cy + 9);  std::cout << ">> 닉네임을 입력하세요: ";
	std::cin >> name;

	// 입력받은 이름 전달
	// Player newPlayer(name);
	GameManager::getInstance().SetPlayer(name); // GameManager용 플레이어 정보 설정

	// 입력 받은 정보 출력
	system("cls"); // 결과창을 위해 클리어

	int resUiX = cx - 30; // 기준위치 30 (60-30)
	int resStartY = cy - 10; // 기준위치 5 (15-10)

	Create_gotoxy(resUiX , resStartY);     std::cout << "============================================================";
	Create_gotoxy(resUiX , resStartY + 1); std::cout << "                  캐릭터 생성이 완료되었습니다.                 ";
	Create_gotoxy(resUiX , resStartY + 2); std::cout << "============================================================";

	int statX = cx - 10; // 스탯 출력 위치 50(60-10)
	Create_gotoxy(statX , resStartY + 4); std::cout << " [ 닉네임 ]   : " << GameManager::getInstance().GetPlayer()->Getstat().name;  // GameManager용 출력
	Create_gotoxy(statX , resStartY + 5); std::cout << " [ Lv ]       : " << GameManager::getInstance().GetPlayer()->Getstat().Level;
	Create_gotoxy(statX , resStartY + 6); std::cout << " [ 체력 ]     : " << GameManager::getInstance().GetPlayer()->Getstat().HP;
	Create_gotoxy(statX , resStartY + 7); std::cout << " [ 공격력 ]   : " << GameManager::getInstance().GetPlayer()->Getstat().Atk_Damage;
	Create_gotoxy(statX , resStartY + 8); std::cout << " [ EXP ]      : " << GameManager::getInstance().GetPlayer()->Getstat().EXP;
	
	Create_gotoxy(resUiX , resStartY + 10); std::cout << "============================================================";

	Create_gotoxy(resUiX , resStartY + 12); system("pause"); // 잠시 멈추기(사용자에게 메시지 보여주기 위해 작성)

	// SceneManager를 통해 다음 씬으로 전환
	SceneManager::getInstance().Replace_Scene(new MainScene());
<<<<<<< HEAD
>>>>>>> update
=======
	return; // 씬이 교체되었으므로 Update 종료
>>>>>>> update
}

// 종료 함수
void CharacterChoice::Exit() {
	// 씬을 나갈 때 메모리 해제 등의 필요한 부분이 있다면 작성
}
