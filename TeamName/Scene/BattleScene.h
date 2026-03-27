#include "Scene.h"

class Player;
class Monster;

class BattleScene :public Scene
{
private:
	Player* player;
	Monster* monster;
	int Player_X = 15 , Player_Y = 4;//Player 이미지 위치
	int Monster_X = 55 , Monster_Y = 4;//Monster 이미지 위치

public:
	~BattleScene() override;
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

