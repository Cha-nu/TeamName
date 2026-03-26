#include "Test_Lobby.h"
#include"Manager/SceneManager/SceneManager.h"
#include"Test_MainScene.h"
#include <iostream>

void Test_Lobby::Init() 
{ 
    system("cls");
}

void Test_Lobby::Render() 
{
    std::cout << "==============================" << std::endl;
    std::cout << "        [ 인생 RPG ]        " << std::endl;
    std::cout << " 1. 게임 시작 (캐릭터 생성)" << std::endl;
}

void Test_Lobby::Update() {
    int input;
    std::cin >> input;
    if (input == 1) {
        // 로비는 일회성이라 쓰자마자 삭제
        SceneManager::getInstance().Replace_Scene(new Test_MainScene());
    }
}

void Test_Lobby::Exit()
{
    std::cout << "Exit call" << std::endl;
}