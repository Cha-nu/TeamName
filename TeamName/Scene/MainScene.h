#include"Scene.h"

class Player;

class MainScene :public Scene
{
private:
	Player* player = nullptr;
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};
