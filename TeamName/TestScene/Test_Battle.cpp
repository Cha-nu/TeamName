#include "Test_Battle.h"
#include"Test_MainScene.h"
#include"../Manager/SceneManager/SceneManager.h"
#include<Windows.h>
#include<iostream>
void Test_Battle::Init()
{
	system("cls");
}

void Test_Battle::Render()
{
	std::cout << "==============================" << std::endl;
	std::cout << "적이 등자하지 않았다...." << std::endl;
	std::cout << "1.마을로 돌아가기 " << std::endl;
}

void Test_Battle::Update()
{
	int input;
	std::cin >> input;
	if ( input == 1 ) {
		// 전투 씬을 팝(Pop)해서 부숴버리고, 밑에 깔린 마을을 다시 깨움!
		SceneManager::getInstance().Return_Scene();
	}
}

void Test_Battle::Exit()
{
	std::cout << "Exit call" << std::endl;
}
