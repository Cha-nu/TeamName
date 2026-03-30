#include "Scene.h"

class Player;
class Inventory;

class InventoryScene :public Scene
{
private:
	Player* player;
	int currentIndex = 0; //인벤토리 창 아이템 '->' 가리키는 위치 변수
	int inventoryState = 0;//인벤토리 씬에 다른 창이 켜져있나를 나타내는 변수
	int confirmIndex = 0;//아이템 사용 결정 팝업창 에서 예, 아니요 '->' 가리키는 변수
	size_t totalItems = 0;
	int popup_X = 15 , popup_Y = 10; //popup 창 위치값
	bool isKeyPressed = false;//키값을 눌렀는지 안눌렀는지 확인하는 값
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

