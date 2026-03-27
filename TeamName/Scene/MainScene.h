#include"Scene.h"

class Player;

class MainScene :public Scene
{
private:
	Player* player = nullptr;
	int currentIndex = 0;
	bool Render_complete = true;
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};
