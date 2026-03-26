// 시작 화면.h

#pragma once
#include "Scene.h"

// 실제 시작 화면 (자식 클래스)
class IntroScene : public Scene {
public:
	IntroScene() {} // 생성자
	~IntroScene() override{} // 부모 클래스의 가상 소멸자를 override

	// 함수 재정의
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};