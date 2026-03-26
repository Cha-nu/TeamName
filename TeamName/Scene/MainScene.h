#include"Scene.h"

//class Player

class MainScene :public Scene
{
private:
	// Player * player -> 캐릭터 정보를 받아와야해서 
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};
