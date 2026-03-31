// 종료 화면.h

#pragma once
#include "../../Scene/Scene.h"

// 실제 시작 화면 (자식 클래스)
class GameOverScene : public Scene {
private:
	int currentIndex = 0; // [0327] 게임 시작용 화살표 추가
public:
	GameOverScene(){} // 생성자
	~GameOverScene() override{} // 부모 클래스의 가상 소멸자를 override

	// 순수 가상 함수
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};