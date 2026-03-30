#include "DrawHelper.h"
#include "ConsoleHelper.h"
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
