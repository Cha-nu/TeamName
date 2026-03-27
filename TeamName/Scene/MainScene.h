#include"Scene.h"

class Player;

class MainScene :public Scene
{
private:
	Player* player = nullptr;
	int artX = 35;//아스키 아트 위치 변수
	int statX = 85;//플레이어 능력치 UI 위치 변수
	int statValX = 96; //플레이어 능력치 값 위치 변수
	int menuX = 35; //선택지 UI 위치 변수
	int currentIndex = 0;//현재 화살표 위치값
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};
