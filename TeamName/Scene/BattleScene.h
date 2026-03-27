#include "Scene.h"

class Player;
class Monster;

class BattleScene :public Scene
{
private:
	Player* player;
	Monster* monster;
public:
	~BattleScene() override;
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

