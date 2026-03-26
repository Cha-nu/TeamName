#include"Scene.h"

class MainScene :public Scene
{
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};
