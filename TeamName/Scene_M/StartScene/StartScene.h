<<<<<<< HEAD
// 시작 화면.h

#pragma once

// 인터페이스 (부모 클래스)
class StartScene {
public:
	StartScene() {} // 기본 생성자
	virtual ~StartScene() {} // 가상 소멸자

	// 순수 가상 함수
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

// 실제 시작 화면 (자식 클래스)
class IntroScene : public StartScene {
public:
	IntroScene() {} // 생성자
	~IntroScene() override{} // 부모 클래스의 가상 소멸자를 override

	// 함수 재정의
=======
癤?/ ?쒖옉 ?붾㈃.h

#pragma once
#include "../../Scene/Scene.h"

// ?ㅼ젣 ?쒖옉 ?붾㈃ (?먯떇 ?대옒??
class StartScene : public Scene {
private:
	int currentIndex = 0; // [0327 異붽?] 寃뚯엫 ?쒖옉???붿궡??
	
public:
	StartScene() {} // ?앹꽦??
	~StartScene() override{} // 遺紐??대옒?ㅼ쓽 媛???뚮㈇?먮? override

	// ?⑥닔 ?ъ젙??
>>>>>>> update
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};