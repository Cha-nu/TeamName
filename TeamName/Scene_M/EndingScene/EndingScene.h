// 엔딩 화면.h

#pragma once
#include "../../Scene/Scene.h"

// EndingScene 클래스
class EndingScene : public Scene {
private:
	int currentIndex = 0;
public:
	EndingScene(){} // 생성자
	~EndingScene() override{} // 부모 클래스의 가상 소멸자 override

	// 함수 재정의
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};

