#pragma once
#include <string>
struct QuizData 
{
	std::string question;    // 문제 내용
	std::string choices[4];  // 보기 1~4
	int correctIndex;        // 정답
};
void DrawMonster(const std::string& monsterName , int x , int y);

QuizData GetRandomQuiz();

void DrawBossEntranceScene();