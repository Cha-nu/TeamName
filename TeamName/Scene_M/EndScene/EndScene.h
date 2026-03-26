// 종료 화면.h

#pragma once
#include "../../Scene/Scene.h"

// 실제 종료 화면 (자식 클래스)
class GameOverScene : public Scene {
public:
	GameOverScene(){} // 생성자
	~GameOverScene() override{} // 부모 클래스의 가상 소멸자를 override

	// 함수 재정의
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};