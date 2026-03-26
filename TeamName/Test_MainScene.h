#pragma once
#include"Scene.h"
class Test_MainScene :public Scene
{
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
	int Save_Date = 0;//씬이 달라져도 맵 데이터 유지가 되는지 확인용
};

