#include "MainScene.h"
#include"BattleScene.h"
#include"Scene/InventoryScene.h"
#include "../Manager/SceneManager/SceneManager.h"
#include"Manager/GameManager/GameManager.h"
#include"Player/Player.h"
#include"ConsoleHelper.h"
#include<iostream>

void MainScene::Init()
{
	system("cls");
	SetCursorVisible(false);
	player = GameManager::getInstance().GetPlayer();
	SceneManager::getInstance().Set_UseItem_Name(""); //메인에서 아이템 저장한 이름 초기화 부분 고민해보기
	SetNeedsRender(true); // 렌더링
	std::cin.clear(); // 입력 버퍼 초기화
	// 이전 씬에서 누른 엔터/스페이스바를 뗄 때까지 무한 대기 (잔상 방지)
	WaitUntilKeyUp_Enter_Space();

	//MainScene일단 전투 상태가 아니니까
	player->bOffPlayerBattle();
}

void MainScene::Render()
{
	if ( !bNeedsRender ) return;
	// 방 아스키 아트 (가운데 배치)
	Console_gotoxy(artX , 2);  std::cout << "         .---------------------------.";
	Console_gotoxy(artX , 3);  std::cout << "         |  _______________________  |";
	Console_gotoxy(artX , 4);  std::cout << "         | |                       | |";
	Console_gotoxy(artX , 5);  std::cout << "         | |  C:\\> KOREA_MAN_HOME  | |";
	Console_gotoxy(artX , 6);  std::cout << "         | |                       | |";
	Console_gotoxy(artX , 7);  std::cout << "         | |_______________________| |";
	Console_gotoxy(artX , 8);  std::cout << "         |                           |";
	Console_gotoxy(artX , 9);  std::cout << "         `---------------------------`";
	Console_gotoxy(artX , 10); std::cout << "               |  |         |  |";
	Console_gotoxy(artX , 11); std::cout << "        _______|__|_________|__|_______";
	Console_gotoxy(artX , 12); std::cout << "       /       [==========]            \\";
	Console_gotoxy(artX , 13); std::cout << "      /  [ ][ ][ ][ ][ ][ ][ ][ ][ ]    \\";
	Console_gotoxy(artX , 14); std::cout << "     /                                   \\";
	Console_gotoxy(artX , 15); std::cout << "    '====================================='";

	// 실시간 스탯창 (오른쪽 배치)
	Console_gotoxy(statX , 4);  std::cout << "+-----------------------+";
	Console_gotoxy(statX , 5);  std::cout << "|   [ 캐릭터 정보 ]     |";
	Console_gotoxy(statX , 6);  std::cout << "+-----------------------+";
	Console_gotoxy(statX , 8);  std::cout << " 이름   : ";
	Console_gotoxy(statX , 10); std::cout << " 레벨   : ";
	Console_gotoxy(statX , 11); std::cout << " HP     : ";
	Console_gotoxy(statX , 12); std::cout << " 공격력 : ";
	Console_gotoxy(statX , 13); std::cout << " 경험치 : ";
	Console_gotoxy(statX , 14); std::cout << " Gold : ";
	Console_gotoxy(statX , 15); std::cout << "+-----------------------+";

	// 실시간 스탯 알맹이 채우기
	// 이름 (문자열이 길 수 있으니 10칸 띄워서 지움)
	Console_gotoxy(statValX , 8);  std::cout << "          ";
	Console_gotoxy(statValX , 8);  std::cout << player->Getstat().name;

	// 2. 레벨
	Console_gotoxy(statValX , 10); std::cout << "    ";
	Console_gotoxy(statValX , 10); std::cout << player->Getstat().Level;

	// 3. HP
	Console_gotoxy(statValX , 11); std::cout << "    ";
	Console_gotoxy(statValX , 11); std::cout << player->Getstat().HP;

	// 4. 공격력
	Console_gotoxy(statValX , 12); std::cout << "    ";
	Console_gotoxy(statValX , 12); std::cout << player->Getstat().Atk_Damage;

	// 5. 경험치
	Console_gotoxy(statValX , 13); std::cout << "    ";
	Console_gotoxy(statValX , 13); std::cout << player->Getstat().EXP;

	// 6. 골드
	Console_gotoxy(statValX , 14); std::cout << "    ";
	Console_gotoxy(statValX , 14); std::cout << player->GetGoldAmount();

	// 하단 메뉴 박스 및 고정 텍스트
	Console_gotoxy(menuX , 18); std::cout << "+------------------------------------------------+";
	Console_gotoxy(menuX , 19); std::cout << "| [ 내 방 ]                                      |";
	Console_gotoxy(menuX , 20); std::cout << "| 다음 목적지를 선택해 주세요.                   |";
	Console_gotoxy(menuX , 21); std::cout << "+------------------------------------------------+";
	Console_gotoxy(menuX , 22); std::cout << "|                                                |";
	Console_gotoxy(menuX , 23); std::cout << "|                                                |";
	Console_gotoxy(menuX , 24); std::cout << "|                                                |";
	Console_gotoxy(menuX , 25); std::cout << "+------------------------------------------------+";

	Console_gotoxy(menuX + 3 , 27); std::cout << "[이동: 방향키(상하좌우) | 선택: SPACE / ENTER]";

	Console_gotoxy(41 , 22); std::cout << "전투 시작";
	Console_gotoxy(65 , 22); std::cout << "아이템 확인 (가방)";
	Console_gotoxy(41 , 24); std::cout << "상점";
	Console_gotoxy(65 , 24); std::cout << "게임 종료";

	Console_gotoxy(38 , 22); std::cout << "  ";
	Console_gotoxy(62 , 22); std::cout << "  ";
	Console_gotoxy(38 , 24); std::cout << "  ";
	Console_gotoxy(62 , 24); std::cout << "  ";

	if ( currentIndex == 0 ) //0 (왼쪽 위)
	{
		Console_gotoxy(38 , 22); std::cout << "->";
	}
	else if ( currentIndex == 1 ) //1 (오른쪽 위)
	{
		Console_gotoxy(62 , 22); std::cout << "->";
	}
	else if ( currentIndex == 2 ) //2 (왼쪽 아래)
	{
		Console_gotoxy(38 , 24); std::cout << "->";
	}
	else if ( currentIndex == 3 ) //3 (오른쪽 아래)
	{
		Console_gotoxy(62 , 24); std::cout << "->";
	}
	SetNeedsRender(false); // 렌더링 잠금
}

void MainScene::Update()
{
	//방향키 위치 이동 정하는 곳
	if ( GetAsyncKeyState(VK_UP) & 0x8000 ) //(방향키 위): 밑에 있는 애들(2, 3)만 위(0, 1)로 갈 수 있음 (이미 위에 있는 0, 1에서 키를 눌러도 무시)
	{
		if ( currentIndex == 2 ) 
		{
			currentIndex = 0;
		}
		else if ( currentIndex == 3 ) 
		{
			currentIndex = 1; 
		}
		SetNeedsRender(true); // 렌더링
	}
	else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) //(방향키 아래): 위에 있는 애들(0, 1)만 아래(2, 3)로 갈 수 있음
	{
		if ( currentIndex == 0 ) 
		{
			currentIndex = 2; 
		}
		else if ( currentIndex == 1 )
		{
			currentIndex = 3;
		}
		SetNeedsRender(true); // 렌더링
	}
	else if ( GetAsyncKeyState(VK_LEFT) & 0x8000 )// (방향키 왼쪽) : 오른쪽에 있는 애들(1 , 3)만 왼쪽(0 , 2)으로 갈 수 있음
	{
		if ( currentIndex == 1 ) 
		{
			currentIndex = 0;
		}
		else if ( currentIndex == 3 ) 
		{ 
			currentIndex = 2; 
		}
		SetNeedsRender(true); // 렌더링
	}
	else if ( GetAsyncKeyState(VK_RIGHT) & 0x8000 ) //(방향 키오른쪽): 왼쪽에 있는 애들(0, 2)만 오른쪽(1, 3)으로 갈 수 있음
	{
		if ( currentIndex == 0 )
		{
			currentIndex = 1;
		}
		else if ( currentIndex == 2 ) 
		{
			currentIndex = 3;
		}
		SetNeedsRender(true); // 렌더링
	}

	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) ) //스페이스나 엔터 누르면
	{
		if ( currentIndex == 0 ) //전투 선택시 
		{
			SceneManager::getInstance().Add_Scene(new BattleScene());
		}
		else if ( currentIndex == 1 ) //아이템 확인
		{
			SceneManager::getInstance().Add_Scene(new InventoryScene());
		}
		else if ( currentIndex == 2 ) //상점
		{
			// SceneManager::getInstance().Add_Scene(new ShopScene());
			//std::cout << "상점 시스템은 아직 준비 중입니다..." << std::endl;
		}
		else if ( currentIndex == 3 ) //게임종료
		{
			system("cls");
			GameManager::getInstance().SetRunning(false);
		}
		SetNeedsRender(true); // 렌더링
	}
	Sleep(50); // 반응 속도 안정화
}

void MainScene::Exit()
{
	system("cls");
}
