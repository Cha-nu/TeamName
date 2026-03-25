
// 게임 실행 파일입니다.

#include <iostream>
#include "Manager/GameManager/GameManager.h"

using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    system("chcp 64001");

    GameManager gameManager;

    // 게임 시작
    gameManager.Run();

    return 0;
}
