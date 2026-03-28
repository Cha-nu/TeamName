// 엔딩 화면.cpp

#include "EndingScene.h"
#include "Manager/SceneManager/SceneManager.h" // Scene 매니저
#include "Scene_M/CreateScene/CreatingCharacter.h" // 씬 전환을 위해 추가

#include <iostream>
#include <string>
#include <windows.h> // [0327 추가] 좌표 이동(gotoxy), GetAsyncKeyState 사용을 위해 추가

// 초기화 함수 (1회 실행)
void EndingScene::Init() {
	// 씬 진입 시 변수 초기화 및 추가할 변수 작성

	// 콘솔 화면 깨끗히 지우기
	system("cls");
}

// 화면 출력
void EndingScene::Render() {

}

// 입력 및 로직 처리
void EndingScene::Update() {

}

// 종료 함수
void EndingScene::Exit() {
	// 씬 나갈 때 메모리 해제 등이 필요하면 작성
}