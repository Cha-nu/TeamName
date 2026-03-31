#include "DrawHelper.h"
#include "ConsoleHelper.h"
#include<vector>
#include <iostream>


void DrawMonster(const std::string& monsterName , int x , int y)
{
	//else if로 추가하면 됨
	if ( monsterName == "수능" )
	{
		// 수능 몬스터 (예: 책장 더미 같은 느낌?)
		Console_gotoxy(x + 3 , y + 3); std::cout << "[수능]";
		Console_gotoxy(x , y + 5); std::cout << "  [======]  ";
		Console_gotoxy(x , y + 6); std::cout << "  |시험지|  ";
		Console_gotoxy(x , y + 7); std::cout << "  | 수능 |  ";
		Console_gotoxy(x , y + 8); std::cout << "  [======]  ";

	}
	else if ( monsterName == "c언어" )
	{
		// 최종 보스
		Console_gotoxy(x + 5 , y + 3); std::cout << "[c언어]";
		Console_gotoxy(x , y + 5); std::cout << "       ( )       ";
		Console_gotoxy(x , y + 6); std::cout << "      --|--* ";
		Console_gotoxy(x , y + 7); std::cout << "        |        ";
		Console_gotoxy(x , y + 8); std::cout << "       / \\       ";
	}
	else if ( monsterName == "c++" )
	{
		Console_gotoxy(x + 6 , y + 3); std::cout << "[c++]";
		Console_gotoxy(x , y + 5); std::cout << "     (0 _ 0)     ";
		Console_gotoxy(x , y + 6); std::cout << "    +[#####]+    "; // 캡슐화 방패
		Console_gotoxy(x , y + 7); std::cout << "     |#####|     ";
		Console_gotoxy(x , y + 8); std::cout << "    _|_____|_    ";

	}
	else if ( monsterName == "graphics" ) 
	{
		Console_gotoxy(x + 4 , y); std::cout << "[graphics]";
		Console_gotoxy(x , y + 2); std::cout << "    .-------.    ";
		Console_gotoxy(x , y + 3); std::cout << "   /   GPU   \\   ";
		Console_gotoxy(x , y + 4); std::cout << "  |  _______  |  ";
		Console_gotoxy(x , y + 5); std::cout << "  | |  (O)  | |  ";
		Console_gotoxy(x , y + 6); std::cout << "  | |_______| |  ";
		Console_gotoxy(x , y + 7); std::cout << "   \\  720p   /   ";
		Console_gotoxy(x , y + 8); std::cout << "    '-------'    ";
	}
	else if ( monsterName == "unreal" )
	{
		Console_gotoxy(x + 7 , y); std::cout << "[unreal]";
		Console_gotoxy(x , y + 1); std::cout << "    --( - U - )--    ";
		Console_gotoxy(x , y + 2); std::cout << "   ===| \\___/ |===   ";
		Console_gotoxy(x , y + 3); std::cout << "      | [[U]] |      ";
		Console_gotoxy(x , y + 4); std::cout << "      |_______|      ";
		Console_gotoxy(x , y + 5); std::cout << "      /       \\      ";
		Console_gotoxy(x , y + 6); std::cout << "     / /|   |\\ \\     ";
		Console_gotoxy(x , y + 7); std::cout << "    /_/ |___| \\_\\    ";
		Console_gotoxy(x , y + 8); std::cout << "       /_____\\       ";
	}
	else if ( monsterName == "취업" )
	{
		Console_gotoxy(x + 7 , y); std::cout << "[취업]";
		Console_gotoxy(x , y + 1); std::cout << "   _____________   ";
		Console_gotoxy(x , y + 2); std::cout << "  |  _________  |  ";
		Console_gotoxy(x , y + 3); std::cout << "  | | [면접] | |  ";
		Console_gotoxy(x , y + 4); std::cout << "  | |  (~_~)  | |  ";
		Console_gotoxy(x , y + 5); std::cout << "  | |_________| |  ";
		Console_gotoxy(x , y + 6); std::cout << "  |    /| |\\    |  ";
		Console_gotoxy(x , y + 7); std::cout << "  |   /_|_|_\\   |  ";
		Console_gotoxy(x , y + 8); std::cout << "  |_____________|  ";
	}
}


static const std::vector<QuizData> bossQuizzes = {
	// 문제 내용, 선택지 4개(무조건 4개), 정답 번호
	{ "Q. 객체지향 프로그래밍(OOP)의 3대 핵심 특징이 아닌 것은?", {"1. 캡슐화", "2. 상속성", "3. 다형성", "4. 휘발성"}, 3 },
};

QuizData GetRandomQuiz()
{
	//퀴즈가 더 늘어아면 랜덤 변수생성
	//int randomIndex = rand() % bossQuizzes.size();
	return bossQuizzes[0];
}
