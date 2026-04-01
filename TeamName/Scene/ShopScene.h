/*
* 일단은 InventoryScene을 참고하여 보일러 플레이트 같아보이는 부분만 작성해보았습니다. --> 
* Shop 클래스에도 각 함수가 무엇을 의미하는지 설명해두었습니다.
* 
* 
*/

#pragma once
#include "Scene.h"
#include "Shop/Shop.h"

class Player;
class Shop;
class ShopScene : public Scene
{
private:
	Player* player;
	// 상점 객체. Shop 파일이 무겁거나 다형성이 고려되지 않기 때문에 Value 타입으로 선언하였습니다.
	// 포인터로 변경해도 문제는 없습니다.
	Shop m_shop; 

	int shopState = 0;    // 0: 상점 메인 메뉴, 1: 구매 창, 2: 판매 창
	int currentIndex = 0; // 아이템 목록이나 메뉴에서 '->' 가리키는 위치 변수
	int confirmIndex = 0; // 팝업창(예/아니오)에서 '->' 가리키는 변수

	size_t maxMenuIndex = 0;
	bool isKeyPressed = false;

	// UI 중앙 배치용 좌표
	int shopX = 0;// ShopUI 위치
	int shopY = 0;
	int popup_X = 0;// 팝업창 위치
	int popup_Y = 0;
	int statX = 0;// 스탯창 위치
	int statY = 0; 
	int nextY = 0;//화살표 위치
	int stockCount = 0;

public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};