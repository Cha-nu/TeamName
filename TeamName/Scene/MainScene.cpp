#include "MainScene.h"
#include"BattleScene.h"
#include"Scene/InventoryScene.h"
#include"Scene/ShopScene.h"
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
	if (!bNeedsRender) return;

	// 콘솔 화면 전체 크기를 가져와서 가운데 좌표 구하기
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	int cx = width / 2;
	int cy = height / 2;

	// 컴포넌트들의 상대적 X, Y 시작 위치 계산 (기준 해상도 대비 비율로 배치)
	int localArtX = cx - 22;  // 방 그림을 중앙보다 조금 왼쪽에
	int localStatX = cx + 27; // 스탯창을 중앙보다 조금 오른쪽에
	int localStatValX = localStatX + 11; // 스탯창 내부 값 쓰기 위치 
	int localMenuX = cx - 25; // 하단 메뉴창을 중앙에
	int localMenuY = cy + 4;  // 하단 메뉴창 높이

	// 1. 방 아스키 아트
	Console_gotoxy(localArtX, cy - 13);  std::cout << "         .---------------------------.";
	Console_gotoxy(localArtX, cy - 12);  std::cout << "         |  _______________________  |";
	Console_gotoxy(localArtX, cy - 11);  std::cout << "         | |                       | |";
	Console_gotoxy(localArtX, cy - 10);  std::cout << "         | |  C:\\> KOREA_MAN_HOME  | |";
	Console_gotoxy(localArtX, cy - 9);   std::cout << "         | |                       | |";
	Console_gotoxy(localArtX, cy - 8);   std::cout << "         | |_______________________| |";
	Console_gotoxy(localArtX, cy - 7);   std::cout << "         |                           |";
	Console_gotoxy(localArtX, cy - 6);   std::cout << "         `---------------------------`";
	Console_gotoxy(localArtX, cy - 5);   std::cout << "               |  |         |  |";
	Console_gotoxy(localArtX, cy - 4);   std::cout << "        _______|__|_________|__|_______";
	Console_gotoxy(localArtX, cy - 3);   std::cout << "       /       [==========]            \\";
	Console_gotoxy(localArtX, cy - 2);   std::cout << "      /  [ ][ ][ ][ ][ ][ ][ ][ ][ ]    \\";
	Console_gotoxy(localArtX, cy - 1);   std::cout << "     /                                   \\";
	Console_gotoxy(localArtX, cy);       std::cout << "    '====================================='";

	// 2. 실시간 스탯창 프레임
	int statStart_Y = cy - 11;
	Console_gotoxy(localStatX, statStart_Y);      std::cout << "+-----------------------+";
	Console_gotoxy(localStatX, statStart_Y + 1);  std::cout << "|   [ 캐릭터 정보 ]     |";
	Console_gotoxy(localStatX, statStart_Y + 2);  std::cout << "+-----------------------+";
	Console_gotoxy(localStatX, statStart_Y + 4);  std::cout << " 이름   : ";
	Console_gotoxy(localStatX, statStart_Y + 6);  std::cout << " 레벨   : ";
	Console_gotoxy(localStatX, statStart_Y + 7);  std::cout << " HP     : ";
	Console_gotoxy(localStatX, statStart_Y + 8);  std::cout << " 공격력 : ";
	Console_gotoxy(localStatX, statStart_Y + 9);  std::cout << " 경험치 : ";
	Console_gotoxy(localStatX, statStart_Y + 10); std::cout << " Gold   : ";
	Console_gotoxy(localStatX, statStart_Y + 11); std::cout << "+-----------------------+";

	// 3. 실시간 스탯 데이터 채우기 (포맷 맞추기 위해 지우고 쓰기)
	Console_gotoxy(localStatValX, statStart_Y + 4);  std::cout << "          ";
	Console_gotoxy(localStatValX, statStart_Y + 4);  std::cout << player->Getstat().name;

	Console_gotoxy(localStatValX, statStart_Y + 6);  std::cout << "    ";
	Console_gotoxy(localStatValX, statStart_Y + 6);  std::cout << player->Getstat().Level;

	Console_gotoxy(localStatValX, statStart_Y + 7);  std::cout << "    ";
	Console_gotoxy(localStatValX, statStart_Y + 7);  std::cout << player->Getstat().HP;

	Console_gotoxy(localStatValX, statStart_Y + 8);  std::cout << "    ";
	Console_gotoxy(localStatValX, statStart_Y + 8);  std::cout << player->Getstat().Atk_Damage;

	Console_gotoxy(localStatValX, statStart_Y + 9);  std::cout << "    ";
	Console_gotoxy(localStatValX, statStart_Y + 9);  std::cout << player->Getstat().EXP;

	Console_gotoxy(localStatValX, statStart_Y + 10); std::cout << "    ";
	Console_gotoxy(localStatValX, statStart_Y + 10); std::cout << player->GetGoldAmount();

	// 4. 하단 메뉴 박스 프레임
	Console_gotoxy(localMenuX, localMenuY);     std::cout << "+------------------------------------------------+";
	Console_gotoxy(localMenuX, localMenuY + 1); std::cout << "| [ 내 방 ]                                      |";
	Console_gotoxy(localMenuX, localMenuY + 2); std::cout << "| 다음 목적지를 선택해 주세요.                   |";
	Console_gotoxy(localMenuX, localMenuY + 3); std::cout << "+------------------------------------------------+";
	Console_gotoxy(localMenuX, localMenuY + 4); std::cout << "|                                                |";
	Console_gotoxy(localMenuX, localMenuY + 5); std::cout << "|                                                |";
	Console_gotoxy(localMenuX, localMenuY + 6); std::cout << "|                                                |";
	Console_gotoxy(localMenuX, localMenuY + 7); std::cout << "+------------------------------------------------+";


	// 조작 설명
	Console_gotoxy(localMenuX + 3, localMenuY + 9); std::cout << "[이동: 방향키(상하좌우) | 선택: SPACE / ENTER]";

	// 메뉴 텍스트 및 선택지 위치 변수 계산 (박스 내부 위치)
	int leftArrowX  = localMenuX + 6;
	int leftTextX   = leftArrowX + 3;
	int rightArrowX = localMenuX + 30;
	int rightTextX  = rightArrowX + 3;

	int topMenuY = localMenuY + 4;
	int botMenuY = localMenuY + 6;

	// 메뉴 텍스트 출력
	Console_gotoxy(leftTextX, topMenuY);  std::cout << "전투 시작";
	Console_gotoxy(rightTextX, topMenuY); std::cout << "아이템 확인";
	Console_gotoxy(leftTextX, botMenuY);  std::cout << "상점";
	Console_gotoxy(rightTextX, botMenuY); std::cout << "게임 종료";

	// 화살표 있던 자리 청소
	Console_gotoxy(leftArrowX, topMenuY);  std::cout << "  ";
	Console_gotoxy(rightArrowX, topMenuY); std::cout << "  ";
	Console_gotoxy(leftArrowX, botMenuY);  std::cout << "  ";
	Console_gotoxy(rightArrowX, botMenuY); std::cout << "  ";

	// 화살표 그리기
	if (currentIndex == 0) // 왼쪽 위
	{
		Console_gotoxy(leftArrowX, topMenuY); std::cout << "->";
	}
	else if (currentIndex == 1) // 오른쪽 위
	{
		Console_gotoxy(rightArrowX, topMenuY); std::cout << "->";
	}
	else if (currentIndex == 2) // 왼쪽 아래
	{
		Console_gotoxy(leftArrowX, botMenuY); std::cout << "->";
	}
	else if (currentIndex == 3) // 오른쪽 아래
	{
		Console_gotoxy(rightArrowX, botMenuY); std::cout << "->";
	}

	Console_gotoxy(0 , 0); //이게 있어야 화살표 움직일때 잔상이 제거됨
	//보이지 않는 커서가 마지막으로 출력한 글자 바로 뒤에 남아있게 되서 윈도우 콘솔 창이 마지막 커서 위치를 화면에 업데이트 할려다가 생기는 문제
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
			SceneManager::getInstance().Add_Scene(new ShopScene());
		}
		else if ( currentIndex == 3 ) //게임종료
		{
			system("cls");
			GameManager::getInstance().SetRunning(false);
			return;
		}
		SetNeedsRender(true); // 렌더링
	}
	Sleep(50); // 반응 속도 안정화
}

void MainScene::Exit()
{
	system("cls");
}
