#include "Scene.h"

class Player;
class Inventory;

class InventoryScene :public Scene
{
private:
	Player* player;//
	Inventory* player_Inventory;
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

