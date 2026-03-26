#include "Scene.h"
class BattleScene :public Scene
{
private:
	//Player * player
	//Monster * monster
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

