#include "MainScene.h"
#include"BattleScene.h"
#include"Player/Player.h"
#include"Monster/Monster.h"
#include "Manager/GameManager/GameManager.h"
#include "Manager/SceneManager/SceneManager.h"
#include"Manager\SoundManager\SoundManager.h"
#include"Scene_M/EndScene/EndScene.h"
#include"Scene/InventoryScene.h"
#include"Scene_M/EndingScene/EndingScene.h"
#include<iomanip>
#include"ConsoleHelper.h"

#include"Data/ItemKey.h"

void BattleScene::Init()
{
	system("cls");
	SetCursorVisible(false);
	std::cin.clear(); // 입력 버퍼 초기화
	SetNeedsRender(true); // 렌더링
	player = GameManager::getInstance().GetPlayer();

	//몬스터 호출 수정
	GameManager::getInstance().CreateMonster(); // IsTutorial = GameManager::getInstance().CreateMonster();로 변경하시면 튜토리얼 보스 여부를 BattleScene에서 알 수 있습니다.
	monster = GameManager::getInstance().GetMonster();//몬스터 동적할당
	monster->getDropTableFromFile();
	//battleScene 들어갈 때 전투상태로 변경
	player->bOnPlayerBattle();

	// 이전 씬에서 누른 엔터/스페이스바를 뗄 때까지 무한 대기 (잔상 방지)
	WaitUntilKeyUp_Enter_Space();
}

void BattleScene::Render()
{
	if ( !bNeedsRender ) 
	{
		return;
	}

	// 전체 화면 크기를 가져와 중앙 좌표(cx, cy) 계산
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	// 상대 좌표 기준 설정값
	Player_X = cx - 27;     
	Player_Y = cy - 13;     
	Monster_X = cx + 13;    
	Monster_Y = cy - 16;    
	
	textX = cx - 45;        
	statX = cx + 25;        
	
	int boxX = cx - 50;     
	int textY = cy;         
	int menuY = cy + 5;     
	int hpY = cy - 5;       

	//플레이어 UI
	Console_gotoxy(Player_X + 4 , Player_Y);     std::cout << "[" << player->Getstat().name << "]";
	Console_gotoxy(Player_X , Player_Y + 2); std::cout << "     (o_o)   "; // 피곤하지만 부릅뜬 눈
	Console_gotoxy(Player_X , Player_Y + 3); std::cout << "    /[_]|\\  "; // 무거운 백팩(또는 노트북 가방)
	Console_gotoxy(Player_X , Player_Y + 4); std::cout << "      | |    ";
	Console_gotoxy(Player_X , Player_Y + 5); std::cout << "     /   \\   ";

	//몬스터 UI
	DrawMonster(monster->getName() , Monster_X , Monster_Y);

	// 실시간 HP 표기
	Console_gotoxy(Player_X + 4, hpY); std::cout << "HP:      ";
	Console_gotoxy(Player_X + 8 , hpY); std::cout << std::left << std::setw(4) << player->Getstat().HP;
	Console_gotoxy(Monster_X + 4 , hpY); std::cout << "HP:      ";
	Console_gotoxy(Monster_X + 8 , hpY); std::cout << std::left << std::setw(4) << monster->getHealth();

	// 무슨 행동이 나오는 텍스트 창
	Console_gotoxy(boxX , textY);     std::cout << "+----------------------------------------------------------------------------------------------------+";
	Console_gotoxy(boxX , textY + 1); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , textY + 2); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , textY + 3); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , textY + 4); std::cout << "+----------------------------------------------------------------------------------------------------+";

	// 메뉴 창
	Console_gotoxy(boxX , menuY);     std::cout << "+----------------------------------------------------------------------------------------------------+";
	Console_gotoxy(boxX , menuY + 1); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , menuY + 2); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , menuY + 3); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , menuY + 4); std::cout << "|                                                                                                    |";
	Console_gotoxy(boxX , menuY + 5); std::cout << "+----------------------------------------------------------------------------------------------------+";

	// 메뉴 글자 / 화살표 배치용 상대 좌표 변수
	int leftText = cx - 19;   
	int rightText = cx + 5;   
	int topMenuRow = cy + 7;  
	int botMenuRow = cy + 9;  

	int leftArr = cx - 22;    
	int rightArr = cx + 2;   

	// 메뉴 고정 텍스트
	if ( battleState != 10 )//문제가 생기면 그냥 바로 밖으로 빼기 
	{
		Console_gotoxy(leftText , topMenuRow); std::cout << "공격";
		Console_gotoxy(rightText , topMenuRow); std::cout << "아이템 (가방)";
		Console_gotoxy(leftText , botMenuRow); std::cout << "능력치 확인";
		Console_gotoxy(rightText , botMenuRow); std::cout << "포기한다";

		Console_gotoxy(leftArr , topMenuRow); std::cout << "  ";
		Console_gotoxy(rightArr , topMenuRow); std::cout << "  ";
		Console_gotoxy(leftArr , botMenuRow); std::cout << "  ";
		Console_gotoxy(rightArr , botMenuRow); std::cout << "  ";
	}
	ClearTextBox();     // 텍스트 창 닦기
	ClearMenuArrows();  // 화살표 사라지게 함
	

	if ( battleState == 0 )//기본 디폴트로 들어오게 함
	{
		//텍스트 출력 부분
		if ( monster->getName() == "취업" )
		{
			//보스 몬스터 텍스트
			Console_gotoxy(textX , textY + 1); std::cout << "이제 일반 몬스터는 상대도 안 된다!";
			Console_gotoxy(textX , textY + 2); std::cout << "보스 [" << monster->getName() << "]이 등장했다!";
		}
		else
		{
			// 기존 일반 몬스터 텍스트
			Console_gotoxy(textX , textY + 1); std::cout << "적 " << monster->getName() << "이(가) 나타났다!";
			Console_gotoxy(textX , textY + 2); std::cout << "무엇을 할까?";
		}

		//화살표 움직여서 어디 고를지 위치 보여줌
		if ( currentIndex == 0 ) //0 (왼쪽 위)
		{
			Console_gotoxy(leftArr , topMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 1 ) //1 (오른쪽 위)
		{
			Console_gotoxy(rightArr , topMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 2 ) //2 (왼쪽 아래)
		{
			Console_gotoxy(leftArr , botMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 3 ) //3 (오른쪽 아래)
		{
			Console_gotoxy(rightArr , botMenuRow); std::cout << "->";
		}
	}
	else if ( battleState == 1 ) //선택지 결과에 따라 나오는 텍스트 출력
	{
		// [상단 박스] 내 공격 결과
		Console_gotoxy(textX , textY + 1); std::cout << "[" << player->Getstat().name << "]의 공격!";
		Console_gotoxy(textX , textY + 2); std::cout << "[" << monster->getName() << "]에게 " << player->Getstat().Atk_Damage << "의 데미지를 주었다!▶(Enter)";
	}
	else if ( battleState == 2 ) 
	{
		// [상단 박스] 승리 결과
		Console_gotoxy(textX , textY + 1); std::cout << "전투에서 승리하였다!! " << monster->getExp() << " 경험치를 획득했다!";
		Console_gotoxy(textX , textY + 2);
		if ( monster_dropItem_name != "" )
		{
			std::cout << "아이템 [" << monster_dropItem_name << "] 과 " << monster_drop_Gold << " Gold를 획득했다! ▶ (Enter)";
		}
		else
		{
			std::cout << monster_drop_Gold << " Gold를 획득했다! ▶ (Enter)";
		}
	}
	else if ( battleState == 3 ) {
		// [상단 박스] 몬스터 공격 결과
		Console_gotoxy(textX , textY + 1); std::cout << "[" << monster->getName() << "]의 공격!";
		Console_gotoxy(textX , textY + 2); std::cout << "[" << player->Getstat().name << "]는 " << monster->getAttack() << "의 데미지를 받았다!  ▶ (Enter)";
	}
	else if ( battleState == 4 ) {
		// [상단 박스] 패배 결과
		Console_gotoxy(textX , textY + 1); std::cout << "[" << player->Getstat().name << "]는 쓰러졌다...";
		Console_gotoxy(textX , textY + 2); std::cout << "눈앞이 깜깜해졌다.  ▶ (Enter)";
	}
	else if ( battleState == 5 ) 
	{
		int stY = cy - 15;

		// [상단 박스] 스탯창 오픈 알림
		Console_gotoxy(textX , textY + 1); std::cout << "캐릭터 능력치를 확인합니다.";
		Console_gotoxy(textX , textY + 2); std::cout << "▶ (Enter를 눌러 닫기)";

		// [우측 팝업] 스탯창 그리기
		Console_gotoxy(statX + 10 , stY + 0);  std::cout << "+-----------------------+";
		Console_gotoxy(statX + 10 , stY + 1);  std::cout << "|   [ 캐릭터 정보 ]     |";
		Console_gotoxy(statX + 10 , stY + 2);  std::cout << "+-----------------------+";
		Console_gotoxy(statX + 10 , stY + 5);  std::cout << " 이름   : " << player->Getstat().name;
		Console_gotoxy(statX + 10 , stY + 7);  std::cout << " 레벨   : " << player->Getstat().Level;
		Console_gotoxy(statX + 10 , stY + 8);  std::cout << " HP     : " << player->Getstat().HP;
		Console_gotoxy(statX + 10 , stY + 9);  std::cout << " 공격력 : " << player->Getstat().Atk_Damage;
		Console_gotoxy(statX + 10 , stY + 10); std::cout << " 경험치 : " << player->Getstat().EXP;
		Console_gotoxy(statX + 10 , stY + 11); std::cout << " Gold   : " << player->GetGoldAmount();
		Console_gotoxy(statX + 10 , stY + 12); std::cout << "+-----------------------+";
	}
	else if ( battleState == 6 ) 
	{
		// [상단 박스] 도망 결과
		Console_gotoxy(textX , textY + 1); std::cout << "의지가 나약한 자여...";
		Console_gotoxy(textX , textY + 2); std::cout << "도망친 자에게는 낙원따윈 없습니다.  ▶ (Enter)";
	}
	else if ( battleState == 7 ) //아이템 사용 텍스트 출력 
	{
		Console_gotoxy(textX , textY + 1); std::cout << "[" << player->Getstat().name << "]는 [" << SceneManager::getInstance().Get_UseItem_Name() << "] 을(를) 사용했다";
		Console_gotoxy(textX , textY + 2); std::cout << "  ▶ (Enter)";
	}
	else if ( battleState == 8 )
	{
		Console_gotoxy(textX , textY + 1); std::cout << "마침내 기나긴 취업 준비생의 끝이 보인다...!";
		Console_gotoxy(textX , textY + 2); std::cout << "보스 [" << monster->getName() << "]을(를) 쓰러뜨렸다! ▶ (Enter)";
	}
	else if ( battleState == 9 ) //보스 몬스터 전용 텍스트 출력 부분
	{
		Console_gotoxy(textX , textY + 1); std::cout << "보스 [" << monster->getName() << "]가 면접 질문을 던졌다!";
		Console_gotoxy(textX , textY + 2); std::cout << "문제를 맞혀야 취업 할 수 있다... ▶ (Enter)";
	}
	else if ( battleState == 10 ) //퀴즈 출제 4지선다
	{
		// 문제 출제(위치 고민)
		Console_gotoxy(textX , textY + 1); std::cout << currentQuiz.question;
		Console_gotoxy(textX , textY + 2); std::cout << "  (방향키로 정답을 선택하고 Enter/Space를 누르세요)";

		// 항목
		Console_gotoxy(leftText , topMenuRow); std::cout << currentQuiz.choices[0] << "        ";
		Console_gotoxy(rightText , topMenuRow); std::cout << currentQuiz.choices[1] << "        ";
		Console_gotoxy(leftText , botMenuRow); std::cout << currentQuiz.choices[2] << "        ";
		Console_gotoxy(rightText , botMenuRow); std::cout << currentQuiz.choices[3] << "        ";

		//화살표 움직여서 어디 고를지 위치 보여줌
		if ( currentIndex == 0 ) //0 (왼쪽 위)
		{
			Console_gotoxy(leftArr , topMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 1 ) //1 (오른쪽 위)
		{
			Console_gotoxy(rightArr , topMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 2 ) //2 (왼쪽 아래)
		{
			Console_gotoxy(leftArr , botMenuRow); std::cout << "->";
		}
		else if ( currentIndex == 3 ) //3 (오른쪽 아래)
		{
			Console_gotoxy(rightArr , botMenuRow); std::cout << "->";
		}
	}
	else if ( battleState == 11 ) // 정답 텍스트
	{
		Console_gotoxy(textX , textY + 1); std::cout << "정답! [" << monster->getName() << "]이 당황했다!";
		Console_gotoxy(textX , textY + 2); std::cout << "[" << monster->getName() << "]에게 치명적인 데미지를 주었다! ▶ (Enter)";
	}
	else if ( battleState == 12 ) // 오답 텍스트
	{
		Console_gotoxy(textX , textY + 1); std::cout << "틀렸습니다....";
		Console_gotoxy(textX , textY + 2); std::cout << "압박감으로 정신적 피해를 입었습니다! ▶ (Enter)";
	}
	Console_gotoxy(0 , 0);

	SetNeedsRender(false); // 렌더링 잠금
}

void BattleScene::Update()
{
	isKeyPressed = false;
	if ( (GetAsyncKeyState(VK_SPACE) & 0x8000) || (GetAsyncKeyState(VK_RETURN) & 0x8000) )
	{
		isKeyPressed = true;
		WaitUntilKeyUp_Enter_Space();
		SetNeedsRender(true); // 렌더링
	}

	if ( battleState == 0 && SceneManager::getInstance().Get_UseItem_Name() != "" )
	{
		battleState = 7;
		SetNeedsRender(true);
	}

	if ( battleState == 0 )//Battle Scene에서 무슨 행동을 할 지 처리하는 부분 (선택지)
	{
		// 방향키 이동 (메뉴에서만 작동)
		if ( GetAsyncKeyState(VK_UP) & 0x8000 ) 
		{
			if ( currentIndex == 2 ) 
			{ 
				if ( currentIndex != 0 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 0;
			}
			else if ( currentIndex == 3 ) 
			{
				if ( currentIndex != 1 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 1;
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 ) 
		{
			if ( currentIndex == 0 ) 
			{ 
				if ( currentIndex != 2 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 2; 
			}
			else if ( currentIndex == 1 ) 
			{ 
				if ( currentIndex != 3 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 3; 
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_LEFT) & 0x8000 ) 
		{
			if ( currentIndex == 1 ) 
			{ 
				if ( currentIndex != 0 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 0; 
			}
			else if ( currentIndex == 3 ) 
			{
				if ( currentIndex != 2 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 2; 
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_RIGHT) & 0x8000 ) 
		{
			if ( currentIndex == 0 ) 
			{
				if ( currentIndex != 1 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 1; 
			}
			else if ( currentIndex == 2 ) 
			{
				if ( currentIndex != 3 ) 
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 3; 
			}
			SetNeedsRender(true); // 렌더링
		}

		// 선택지 결정
		if ( isKeyPressed )
		{
			if ( currentIndex == 0 )
			{
				
				system("cls"); // 화면 한 번 지워주기

				// 타격 연출
				DrawFistEffect();

				Sleep(200);

				// 피격 연출 
				// 몬스터의 X, Y 좌표 계산
				CONSOLE_SCREEN_BUFFER_INFO csbi;
				GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE) , &csbi);
				int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
				int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;
				

				// 3번 깜빡이기
				for ( int i = 0; i < 3; i++ ) {
					system("cls");
					Sleep(100);

					
					bNeedsRender = true;
					Render();
					Sleep(100);
				}

				// 데미지 계산 및 상태 전환
				player->Attack(monster);
				battleState = 1;

				SetNeedsRender(true); // 텍스트를 포함해 다시 렌더링
			}
			else if ( currentIndex == 1 ) {
				SceneManager::getInstance().Add_Scene(new InventoryScene());
			}
			else if ( currentIndex == 2 ) {
				battleState = 5; // 스탯창 띄움
			}
			else if ( currentIndex == 3 ) {
				battleState = 6;
			}
			SetNeedsRender(true); 
		}
	}
	else if ( battleState == 1 ) //플레이어 몬스터 공격 상호작용
	{
		if ( isKeyPressed )
		{
			if ( monster->isDead() ) 
			{
				player->AcquireEXP(monster->getExp());
				monster_drop_Gold = monster->getDropGold();
				player->AcquireGold(monster_drop_Gold);
				ItemSlot dropItem = monster->getDropItem();
				if ( dropItem.GetItem() != nullptr ) 
				{
					monster_dropItem_name = dropItem.GetItem()->GetName();
					player->GetInventory()->AddItem(dropItem.GetItem()->GetID() , 1);
				}

				if ( monster->getName() == "취업" ) 
				{ 
					battleState = 8; 
				}
				else 
				{ 
					battleState = 2;
				}
			}
			else 
			{
				if ( monster->getName() == "취업" ) 
				{ 
					battleState = 9; 
				}
				else 
				{
					monster->attackPlayer(player);
					battleState = 3;
				}
			}
			//SetNeedsRender(true);
		}
	}
	else if ( battleState == 2 ) // 승리 텍스트 후
	{ 
		if ( isKeyPressed )
		{
			player->bOffPlayerBattle();
			SceneManager::getInstance().Return_Scene(); 
		} 
	}
	else if ( battleState == 3 ) // 몬스터 공격 후 처리
	{ 
		if ( isKeyPressed )
		{
			if ( player->Getstat().HP <= 0 ) battleState = 4;
			else battleState = 0; 
		}
	}
	else if ( battleState == 4 ) // 플레이어가 죽으면 처리하는 로직 
	{ 
		if ( isKeyPressed )
		{
			player->bOffPlayerBattle();
			SceneManager::getInstance().Replace_Scene(new GameOverScene());
		} 
	}
	else if ( battleState == 5 ) // 스탯창 열려있을 때
	{ 
		if ( isKeyPressed )
		{
			ClearStatBox(); 
			battleState = 0; 
		}
	}
	else if ( battleState == 6 ) // 도망간다 선택하면 처리하는 로직 
	{ 
		if ( isKeyPressed ) 
		{ 
			player->bOffPlayerBattle();
			SceneManager::getInstance().Replace_Scene(new GameOverScene()); 
		}
	}
	else if ( battleState == 7 ) //아이템 사용 후 몬스터한테 턴 넘어가는 로직
	{
		if ( isKeyPressed ) 
		{
			SceneManager::getInstance().Set_UseItem_Name("");
			if ( monster->isDead() ) battleState = 2; 
			else
			{
				if ( monster->getName() == "취업" ) 
				{ 
					battleState = 9;
				}
				else
				{
					monster->attackPlayer(player);
					battleState = 3;
				}
			}
			SetNeedsRender(true);
		}
	}
	else if ( battleState == 8 ) //보스잡고나서 처리하는 부분
	{
		if ( isKeyPressed )
		{
			player->bOffPlayerBattle();
			SceneManager::getInstance().Replace_Scene(new EndingScene());
		}
	}
	else if ( battleState == 9 ) //퀴즈 처리 부분
	{
		if ( isKeyPressed )
		{
			currentQuiz = GetRandomQuiz(); // 헬퍼에서 문제 하나 뽑아오기!
			battleState = 10;
			currentIndex = 0;
			system("cls"); // 잔상 깔끔하게 청소
			SetNeedsRender(true);
		}
	}
	else if ( battleState == 10 ) //퀴즈 4지선다 고르고 작동하는 부분
	{
		if ( GetAsyncKeyState(VK_UP) & 0x8000 )
		{
			if ( currentIndex == 2 )
			{
				if ( currentIndex != 0 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 0;
			}
			else if ( currentIndex == 3 )
			{
				if ( currentIndex != 1 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 1;
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_DOWN) & 0x8000 )
		{
			if ( currentIndex == 0 )
			{
				if ( currentIndex != 2 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 2;
			}
			else if ( currentIndex == 1 )
			{
				if ( currentIndex != 3 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 3;
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_LEFT) & 0x8000 )
		{
			if ( currentIndex == 1 )
			{
				if ( currentIndex != 0 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 0;
			}
			else if ( currentIndex == 3 )
			{
				if ( currentIndex != 2 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 2;
			}
			SetNeedsRender(true); // 렌더링
		}
		else if ( GetAsyncKeyState(VK_RIGHT) & 0x8000 )
		{
			if ( currentIndex == 0 )
			{
				if ( currentIndex != 1 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 1;
			}
			else if ( currentIndex == 2 )
			{
				if ( currentIndex != 3 )
				{
					SoundManager::GetInstance().PlayEffectSound("Music/Select_Sound.wav");
				}
				currentIndex = 3;
			}
			SetNeedsRender(true); // 렌더링
		}

		if ( isKeyPressed )
		{
			system("cls"); // 잔상 지우기
			if ( currentIndex == currentQuiz.correctIndex ) // 정답!
			{
				battleState = 11;
				// 정답시 보스한테 어떻게 피해를 줄지
				player->Attack(monster);
			}
			else // 오답
			{
				battleState = 12;
				//플레이어 처리 부분
				monster->attackPlayer(player);
			}
			SetNeedsRender(true);
		}
	}
	else if ( battleState == 11 || battleState == 12 ) // 퀴즈 결과 확인 후
	{
		if ( isKeyPressed )
		{
			system("cls");
			if ( player->Getstat().HP <= 0 ) // 체력 다 닳았으면 게임오버
			{ 
				battleState = 4; 
			} 
			else if ( monster->isDead() ) // 보스가 죽었으면 엔딩
			{ 
				battleState = 8; 
			}    
			else// 둘다 살았으면 행동 선택화면으로 
			{
				battleState = 0; 
				currentIndex = 0;
			}
			SetNeedsRender(true);
		}
	}

	Sleep(50);
}

void BattleScene::Exit()
{
	system("cls");
}

void BattleScene::ClearTextBox()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	int textY = cy; 
	int tX = cx - 45;

	for ( int i = textY + 1; i <= textY + 2; i++ ) 
	{
		Console_gotoxy(tX , i);
		std::cout << "                                                                                ";
	}
}

void BattleScene::ClearMenuArrows()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	int leftArr = cx - 22; 
	int rightArr = cx + 2; 
	int topMenuRow = cy + 7;
	int botMenuRow = cy + 9;

	Console_gotoxy(leftArr , topMenuRow); std::cout << "  ";
	Console_gotoxy(rightArr , topMenuRow); std::cout << "  ";
	Console_gotoxy(leftArr , botMenuRow); std::cout << "  ";
	Console_gotoxy(rightArr , botMenuRow); std::cout << "  ";
}

void BattleScene::ClearStatBox()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	int sX = cx + 35; 
	int stY = cy - 15; 

	for ( int i = stY; i <= stY + 14; i++ ) 
	{
		Console_gotoxy(sX , i);
		std::cout << "                         "; // 공백 25칸으로 덮어서 지움
	}
}

BattleScene::~BattleScene()
{
	//동적할당 받은 몬스터 메모리 해제
	//delete monster;
}

void BattleScene::DrawFistEffect()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	int cx = (csbi.srWindow.Right - csbi.srWindow.Left + 1) / 2;
	int cy = (csbi.srWindow.Bottom - csbi.srWindow.Top + 1) / 2;

	// 기존 화면에 덮어 씌울 상대 좌표 계산
	int fistX = cx - 20; 
	int fistY = cy - 14;  

	//  주먹 출력 연출
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                     :#=@@#             )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                .   ;* ~@@@@@@@:.       )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(              ,=@@=*    * ***,;@!       )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(          ,,,##~;*   ,#$,      *=       )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(         @@@@:              !$.!@       )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(       #!,#    $;               ;*      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(      $-                        :=      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(      ! *;;               ,      @      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(     $,           .       *      @      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(     $            ,      .       @      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(    *,.     =     ,      ~       @      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(    @ ~     @     ,      $       @      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(    @ ~     @     :      $      ~=      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(    @~*     @     @      @      :*      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(    .@@     @.    -      @      :=      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(     $@-    @,    ,$     @      :*      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(      #:    @,    ,@     @ !!!!!=$$     )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(      *#    @,    ,@:   .@@@@@=-  *=    )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(       @    @@;---@@@@@@@** :*@~  ,@    )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(       #@@@@$~$$$$$$   @    ,  .  ,#    )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(        =#@@@@@@@!     $     ,    -     )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                      !:     ,    @     )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                      @!    $   * $     )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                      *@    @   !-*     )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                       @@$!=    .*      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                       -!!!!$@*:#:      )";
	Console_gotoxy(fistX, fistY++);      std::cout << R"(                               ~:       )";
}

