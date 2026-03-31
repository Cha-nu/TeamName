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
	{ "Q. 큐(Queue)의 가장 기본적인 작동 원리를 설명하는 용어는?", {"1. First in First out", "2. First in Last out", "3. Last in First out", "4. 보기 중 없음"}, 0 },
	{ "Q. 가상함수를 자식 클래스에서 더 이상 오버라이딩 하지 못하도록 하는 키워드는?", {"1. override", "2. final", "3. friend", "4. const"}, 1 },
	{ "Q. 다음 중 C++에서 데이터를 외부로 내보내는 '출력' 기능이 아닌 것은?", {"1. std::cout", "2. printf()", "3. console.log()", "4. std::cerr"}, 2 },
	{ "Q. 한 번 지정한 변수 값을 고정시켜 변하지 않게 만드는 키워드는?", {"1. virtual", "2. static", "3. const", "4. class"}, 2 },
	{ "Q. 언리얼 C++에서 게임 화면에 디버그 메시지를 출력하는 함수 이름은?", {"1. UE_LOG", "2. FString::Printf", "3. TEXT", "4. AddOnScreenDebugMessage"}, 3 },
	{ "Q. vector자료형의 함수중 일반적으로 시간복잡도가 다른것은?", {"1. push_back()", "2. erase()", "3.at()", "4. pop_back()"}, 1 },
	{ "Q. 다음 보기 중 SOLID 원칙에 해당하지 않는 예시는?", {"1. 단일 책임", "2. 개방-폐쇄", "3. 리스코프 치환", "4. 인터페이스 병합"}, 3 },
	{ "Q. 보기 중 unique_ptr, shared_ptr과 같은 클래스를 부르는 말로 옳은 것은?", {"1. 스마트 포인터", "2. 하이퍼 포인터", "3. 특수 포인터", "4. 사용자 정의 포인터"}, 0 },
	{ "Q. 부모 클래스의 멤버변수를 자식이 사용하게 하기 위해 사용하는 최소 접근 제한자는?", {"1. public", "2. protected", "3. private", "4. 접근제한자 생략"}, 1 },
	{ "Q. 다음 중 MyClass 클래스의 생성자로 올바르게 선언된 것은?", {"1. virtual MyClass()", "2. virtual MyClass()=0", "3. MyClass()", "4. ~MyClass()"}, 2 },
};

QuizData GetRandomQuiz()
{
	//퀴즈가 더 늘어아면 랜덤 변수생성
	int randomIndex = rand() % bossQuizzes.size();
	return bossQuizzes[randomIndex];
}
