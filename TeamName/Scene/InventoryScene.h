#include "Scene.h"

class Player;
class Inventory;

class InventoryScene :public Scene
{
private:
	Player* player;//
	Inventory* player_Inventory;
	std::vector<ItemSlot>& player_ItemSlots;
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

