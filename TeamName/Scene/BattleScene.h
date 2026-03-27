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
	int currentIndex = 0;//현재 화살표 위치값
	int battleState = 0;
	int textX = 14;//텍스트 위치
	int statX = 85;//스택창 위치
	bool isEnterPressed = false;//
	void ClearTextBox();//텍스트 삭제하는 부분
	void ClearMenuArrows();//텍스트 나올 때 화살표 사라지게 해서 선택이 안되게
	void ClearStatBox();//능력치 팝업창 삭제
public:
	~BattleScene() override;
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

