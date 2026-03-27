// 시작 화면.h

#pragma once
#include "../../Scene/Scene.h"

// 실제 시작 화면 (자식 클래스)
class StartScene : public Scene {
private:
	int currentIndex = 0; // [0327 추가] 게임 시작용 화살표
public:
	StartScene() {} // 생성자
	~StartScene() override{} // 부모 클래스의 가상 소멸자를 override

	// 함수 재정의
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};