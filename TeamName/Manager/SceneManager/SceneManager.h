#pragma once
#include<stack>
class Scene;

class SceneManager
{
private:
	std::stack<Scene*>SceneStack; //씬들이 들어가서 저장되는 stack
	SceneManager() {}; //외부 생성금지

public:
	void Render();//UI이미지를 계속 출력하는 부분

	void Update();//계산처리를 계속 갱신하는 부분 

	void Add_Scene(Scene* newScene);//SceneStack 씬을 추가하는 함수

	void Return_Scene();//현재 돌고있는 Scene을 나가고 이전에 저장되어있는 Scene으로 돌아가기 (주로 씬이 들고있는 데이터를 가지고 있어야하고 씬을 바꿔야 할 때)
	//선택화면으로 돌아갈 때 쓰는 함수

	void Replace_Scene(Scene* newScene);//현재 씬을 내보내고 바로 새로운 씬을 넣는 함수(씬이 들고있는 데이터 저장이 필요없을때)
	//타이틀화면,이벤트화면,전투화면등 일회성으로 사용하는 씬들

	void SceneStack_Clear(); //게임매니저 Release에서만 사용 (메모리 누수 방지)
	//게임을 종료하거나 전투 중간에 게임을 종료하고 싶을 때 남아있는 SceneStack을 비워준다.



	static SceneManager& getInstance()//씬 매니저를 외부코드에서 사용하고 싶으면 사용하는 함수 (싱글톤)
	{
		static SceneManager instance;
		return instance;
	}

	SceneManager(const SceneManager&) = delete; //복사 방지(싱글톤)
	SceneManager& operator=(const SceneManager&) = delete; //대입 방지 (싱글톤)

};

