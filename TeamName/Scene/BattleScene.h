#include "Scene.h"
class BattleScene :public Scene
{
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

