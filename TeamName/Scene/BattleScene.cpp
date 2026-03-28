#include "MainScene.h"
#include"BattleScene.h"
#include"Player/Player.h"
#include"Monster/Monster.h"
#include"../Manager/GameManager/GameManager.h"
#include "../Manager/SceneManager/SceneManager.h"
#include"Scene_M/EndScene/EndScene.h"
#include"Scene\InventoryScene.h"
#include<iostream>
#include<iomanip>
#include"ConsoleHelper.h"

#include "Manager/GameManager/GameManager.h"

void BattleScene::Init()
{
	system("cls");
	SetCursorVisible(true);
	std::cin.clear(); // 입력 버퍼 초기화
	player = GameManager::getInstance().GetPlayer();

	//몬스터 호출 수정
	GameManager::getInstance().CreateMonster(); // IsTutorial = GameManager::getInstance().CreateMonster();로 변경하시면 튜토리얼 보스 여부를 BattleScene에서 알 수 있습니다.
	monster = GameManager::getInstance().GetMonster();//몬스터 동적할당
	

	// 이전 씬에서 누른 엔터/스페이스바를 뗄 때까지 무한 대기 (잔상 방지)
	WaitUntilKeyUp_Enter_Space();
	
}

void BattleScene::Render()
{

	//플레이어 UI
	Console_gotoxy(Player_X , Player_Y);     std::cout << "[" << player->Getstat().name << "]";
	Console_gotoxy(Player_X , Player_Y + 2); std::cout << "      O     ";
	Console_gotoxy(Player_X , Player_Y + 3); std::cout << "     /|\\    ";
	Console_gotoxy(Player_X , Player_Y + 4); std::cout << "     / \\    ";

	//몬스터 UI
	Console_gotoxy(Monster_X , Monster_Y);     std::cout << "[" << monster->getName() << "]";
	Console_gotoxy(Monster_X , Monster_Y + 2); std::cout << "      O     ";
	Console_gotoxy(Monster_X , Monster_Y + 3); std::cout << "     /|\\    ";
	Console_gotoxy(Monster_X , Monster_Y + 4); std::cout << "     / \\    ";

	// 실시간 HP 표기
	Console_gotoxy(Player_X , 10); std::cout << "HP:      ";
	Console_gotoxy(Player_X + 4 , 10); std::cout << std::left << std::setw(4) << player->Getstat().HP;
	Console_gotoxy(Monster_X , 10); std::cout << "HP:      ";
	Console_gotoxy(Monster_X + 4 , 10); std::cout << std::left << std::setw(4) << monster->getHealth();

	// 무슨 행동이 나오는 텍스트 창
	Console_gotoxy(10 , 15); std::cout << "+----------------------------------------------------------------------------------------------------+";
	Console_gotoxy(10 , 16); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 17); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 18); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 19); std::cout << "+----------------------------------------------------------------------------------------------------+";

	// 메뉴 창
	Console_gotoxy(10 , 20); std::cout << "+----------------------------------------------------------------------------------------------------+";
	Console_gotoxy(10 , 21); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 22); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 23); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 24); std::cout << "|                                                                                                    |";
	Console_gotoxy(10 , 25); std::cout << "+----------------------------------------------------------------------------------------------------+";

	// 메뉴 고정 텍스트
	Console_gotoxy(41 , 22); std::cout << "공격";
	Console_gotoxy(65 , 22); std::cout << "아이템 (가방)";
	Console_gotoxy(41 , 24); std::cout << "능력치 확인";
	Console_gotoxy(65 , 24); std::cout << "포기한다";

	Console_gotoxy(38 , 22); std::cout << "  ";
	Console_gotoxy(62 , 22); std::cout << "  ";
	Console_gotoxy(38 , 24); std::cout << "  ";
	Console_gotoxy(62 , 24); std::cout << "  ";

	ClearTextBox();     // 텍스트 창 닦기
	ClearMenuArrows();  // 화살표 사라지게 함
	if ( battleState == 0 )//기본 디폴트로 들어오게 함
	{
		//텍스트 출력 부분
		Console_gotoxy(textX , 16); std::cout << "적 " << monster->getName() << "이(가) 나타났다!";
		Console_gotoxy(textX , 17); std::cout << "무엇을 할까?";

		//화살표 움직여서 어디 고를지 위치 보여줌
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
	}
	else if ( battleState == 1 ) //선택지 결과에 따라 나오는 텍스트 출력
	{
		// [상단 박스] 내 공격 결과
		Console_gotoxy(textX , 16); std::cout << "플레이어의 공격!";
		Console_gotoxy(textX , 17); std::cout << "몬스터에게 " << player->Getstat().Atk_Damage << "의 데미지를 주었다!  ▶ (Enter)";
	}
	else if ( battleState == 2 ) {
		// [상단 박스] 승리 결과
		Console_gotoxy(textX , 16); std::cout << "전투에서 승리하였다!!";
		Console_gotoxy(textX , 17); std::cout << "전리품을 획득하고 마을로 돌아갑니다.  ▶ (Enter)";
	}
	else if ( battleState == 3 ) {
		// [상단 박스] 몬스터 공격 결과
		Console_gotoxy(textX , 16); std::cout << "몬스터의 공격!";
		Console_gotoxy(textX , 17); std::cout << "플레이어는 " << monster->getAttack() << "의 데미지를 받았다!  ▶ (Enter)";
	}
	else if ( battleState == 4 ) {
		// [상단 박스] 패배 결과
		Console_gotoxy(textX , 16); std::cout << "플레이어는 쓰러졌다...";
		Console_gotoxy(textX , 17); std::cout << "눈앞이 깜깜해졌다.  ▶ (Enter)";
	}
	else if ( battleState == 5 ) 
	{
		// [상단 박스] 스탯창 오픈 알림
		Console_gotoxy(textX , 16); std::cout << "캐릭터 능력치를 확인합니다.";
		Console_gotoxy(textX , 17); std::cout << "▶ (Enter를 눌러 닫기)";

		// [우측 팝업] 스탯창 그리기
		Console_gotoxy(statX , 0);  std::cout << "+-----------------------+";
		Console_gotoxy(statX , 1);  std::cout << "|   [ 캐릭터 정보 ]     |";
		Console_gotoxy(statX , 2);  std::cout << "+-----------------------+";
		Console_gotoxy(statX , 5);  std::cout << " 이름   : " << player->Getstat().name;
		Console_gotoxy(statX , 7); std::cout << " 레벨   : " << player->Getstat().Level;
		Console_gotoxy(statX , 8); std::cout << " HP     : " << player->Getstat().HP;
		Console_gotoxy(statX , 9); std::cout << " 공격력 : " << player->Getstat().Atk_Damage;
		Console_gotoxy(statX , 10); std::cout << " 경험치 : " << player->Getstat().EXP;
		Console_gotoxy(statX , 12); std::cout << "+-----------------------+";
	}
	else if ( battleState == 6 ) 
	{
		// [상단 박스] 도망 결과
		Console_gotoxy(textX , 16); std::cout << "의지가 나약한 자여...";
		Console_gotoxy(textX , 17); std::cout << "도망치다 몬스터에게 당했습니다.  ▶ (Enter)";
	}
	else if ( battleState == 7 ) //아이템 사용 텍스트 출력 
	{
		Console_gotoxy(textX , 16); std::cout << "플레이어는 [" << GameManager::getInstance().Get_UseItem_Name() << "] 을(를) 사용했다";
		Console_gotoxy(textX , 17); std::cout << "  ▶ (Enter)";
	}
}

void BattleScene::Update()
{
	isKeyPressed = false;
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;
		WaitUntilKeyUp_Enter_Space();
	}

	if ( battleState == 0 && GameManager::getInstance().Get_UseItem_Name() != "" )//만약 아이템을 사용하고 왔다면
	{
		battleState = 7;
	}

	if ( battleState == 0 )//Battle Scene에서 무슨 행동을 할 지 처리하는 부분 (선택지)
	{
		// 방향키 이동 (메뉴에서만 작동)
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			if ( currentIndex == 2 ) 
			{
				currentIndex = 0; 
			}
			else if ( currentIndex == 3 ) 
			{
				currentIndex = 1;
			}
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			if ( currentIndex == 0 ) 
			{
				currentIndex = 2;
			}
			else if ( currentIndex == 1 ) 
			{
				currentIndex = 3;
			}
		}
		else if ( GetAsyncKeyState(VK_LEFT) & 0x8000 ) 
		{
			if ( currentIndex == 1 ) 
			{
				currentIndex = 0;
			} 
			else if ( currentIndex == 3 ) 
			{
				currentIndex = 2;
			} 
		}
		else if ( GetAsyncKeyState(VK_RIGHT) & 0x8000 ) 
		{
			if ( currentIndex == 0 ) 
			{
				currentIndex = 1;
			} 
			else if ( currentIndex == 2 ) 
			{
				currentIndex = 3;
			} 
		}

		// 선택지 결정
		if ( isKeyPressed )
		{
			if ( currentIndex == 0 ) 
			{
				player->Attack(monster);
				battleState = 1; // 내 공격 텍스트 출력 상태로!
			}
			else if ( currentIndex == 1 ) {
				// 2. 인벤토리
				SceneManager::getInstance().Add_Scene(new InventoryScene());
			}
			else if ( currentIndex == 2 ) {
				// 3. 능력치 확인
				battleState = 5; // 스탯창 띄움
			}
			else if ( currentIndex == 3 ) {
				// 4. 포기
				battleState = 6;
			}
		}
	}
	else if ( battleState == 1 ) //몬스터 공격 텍스트 출력
	{
		if ( isKeyPressed )
		{
			if ( monster->isDead() ) 
			{
				battleState = 2; // 승리!
			}
			else 
			{
				// 몬스터 살아있으면 반격
				monster->attackPlayer(player);
				battleState = 3; // 몬스터 공격 텍스트 출력 상태로!
			}
		}
	}
	else if ( battleState == 2 ) // 승리 텍스트 후
	{ 
		if ( isKeyPressed )
		{
			SceneManager::getInstance().Return_Scene(); // 메인으로
		} 
	}
	else if ( battleState == 3 ) // 몬스터 공격 후 처리
	{ 
		if ( isKeyPressed )
		{
			if ( player->Getstat().HP <= 0 ) 
			{
				battleState = 4; // 패배
			}
			else 
			{
				battleState = 0; // 살았으니 다시 내 턴 (선택지로 돌아가기)
			}
		}
	}
	else if ( battleState == 4 ) // 플레이어가 죽으면 처리하는 로직 
	{ 
		if ( isKeyPressed )
		{
			SceneManager::getInstance().Replace_Scene(new GameOverScene());
		} 
	}
	else if ( battleState == 5 ) // 스탯창 열려있을 때
	{ 
		if ( isKeyPressed )
		{
			ClearStatBox(); // 스탯창 삭제
			battleState = 0; // 다시 메뉴 상태로 돌아감
		}
	}
	else if ( battleState == 6 ) // 도망간다 선택하면 처리하는 롲기 
	{ 
		if ( isKeyPressed ) SceneManager::getInstance().Replace_Scene(new GameOverScene());
	}
	else if ( battleState == 7 ) //아이템 사용 후 몬스터한테 턴 넘어가는 로직=
	{
		if ( isKeyPressed ) 
		{
			if ( monster->isDead() )
			{
				battleState = 2; // 승리!
			}
			else
			{
				// 몬스터 살아있으면 반격
				monster->attackPlayer(player);
				battleState = 3; // 몬스터 공격 텍스트 출력 상태로!
			}
		}
	}

	Sleep(50);

	//if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) ) 
	//{
	//	//if currentIndex == 0 을 선택하면
	//	// 선택할수 있는 화살표가 사라지고
	//	//플레이어가 몬스터를 공격한다는걸 텍스트 문구 창에 나오고 데미지도 얼마주는지도 2줄로 깔끔하게 보여준다
	//	//엔터를 누르면 텍스트가 사라지고
	//	//이제 몬스터가 공격한다
	//	    // if 만약 몬스터가 죽었다면 이겼다고 문구가 나오고 그 다음줄에 골드나 인벤토리 뭘 얻었다고 문구가 나온다.
	//	    // 엔터를 누르면 Main Scene으로 넘어간다.
	//	//몬스터가 플레이어를 공격한다는게 텍스트 문구 창에 나오고 데미지도 얼마주는지도 2줄로 깔끔하게 보여준다
	//	//엔터를 누르면 텍스트가 사라진다
	//	   // if 플레이어가 몬스터 공격에 죽었다면 죽었다 라는 문구가 나온다.
	//	   // 엔터를 누르면 GameOverScene으로 넘어간다.
	//	//다시 선택지로 돌아가고 화살표가 나온다
	//	
	//	//if currentIndex == 1을 선택하면
	//	//인벤토리 씬으로 넘어간다.
	//
	//	//if currentIndex == 2을 선택하면
	//	// 선택할 수 있는 화살표가 사라지고
	//	// UI씬에 캐릭터 능력치가 어떤지 나온다 
	//	// 엔터를 누르면
	//	// UI씬이 사라지고 화살표가 다시 나오고 선택지로 간다
	//
	//	//if currentIndex == 3을 선택하면
	//	//의지가 나약한자라고 문구가 나오고 
	//	//엔터나 스페이스를 누르면 GameOver씬으로 넘어가게 해줘
	//}

}

void BattleScene::Exit()
{
}

void BattleScene::ClearTextBox()
{
	for ( int i = 17; i <= 18; i++ ) 
	{
		Console_gotoxy(15 , i);
		std::cout << "                                                                                ";
	}
}

void BattleScene::ClearMenuArrows()
{
	Console_gotoxy(38 , 22); std::cout << "  ";
	Console_gotoxy(62 , 22); std::cout << "  ";
	Console_gotoxy(38 , 24); std::cout << "  ";
	Console_gotoxy(62 , 24); std::cout << "  ";
}

void BattleScene::ClearStatBox()
{
	for ( int i = 3; i <= 14; i++ ) 
	{
		Console_gotoxy(85 , i);
		std::cout << "                         "; // 공백 25칸으로 덮어서 지움
	}
}

BattleScene::~BattleScene()
{
	//동적할당 받은 몬스터 메모리 해제
	//delete monster;
}

