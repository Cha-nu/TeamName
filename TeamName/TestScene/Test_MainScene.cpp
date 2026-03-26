#include "Test_MainScene.h"
#include"Test_Battle.h"
#include<iostream>
#include <Windows.h>
#include"../Manager/SceneManager/SceneManager.h"

void Test_MainScene::Init()
{
	system("cls");
}

void Test_MainScene::Render()
{
	std::cout << "==============================" << std::endl;
	std::cout << "데이터가 유지되는지 확인용: " << Save_Date << std::endl;
	std::cout << "1.전투 씬으로 가기 " << std::endl;
}

void Test_MainScene::Update()
{
	int input;
	std::cin >> input;
	if ( input == 1 ) {
		// 마을 데이터 유지가 되야하니 씬 추가로 위에 올림
		SceneManager::getInstance().Add_Scene(new Test_Battle());
	}

}


void Test_MainScene::Exit()
{
	std::cout << "Exit call" << std::endl;
	Save_Date++;
}
