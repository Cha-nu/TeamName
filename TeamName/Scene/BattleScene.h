#include "Scene.h"
#include<string>

class Player;
class Monster;

class BattleScene :public Scene
{
private:
	Player* player;
	Monster* monster;
	std::string monster_dropItem_name = "";
	int monster_drop_Gold = 0;
	int Player_X = 15 , Player_Y = 3;//Player 이미지 위치
	int Monster_X = 55 , Monster_Y = 0;//Monster 이미지 위치
	int currentIndex = 0;//현재 화살표 위치값
	int battleState = 0;//battle씬에서 현재 무슨상태인지(무슨 처리를 해야하고 무슨 텍스트를 출력해야하는지 정하는 변수)
	int textX = 14;//텍스트 위치
	int statX = 85;//스택창 위치
	bool isKeyPressed = false;//키를 눌렀는지 안눌렀는지 확인하는 값
	void ClearTextBox();//텍스트 삭제하는 부분
	void ClearMenuArrows();//텍스트 나올 때 화살표 사라지게 해서 선택이 안되게
	void ClearStatBox();//능력치 팝업창 삭제
	void DrawFistEffect(); // 공격할 때 타격감 주는 효과
public:
	~BattleScene() override;
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
	
};

