#pragma once
#include<stack>
class Scene;

class SceneManager
{
private:
	std::stack<Scene*>stateStack; //씬들이 들어가서 저장되는 stack
	SceneManager() {}; //외부 생성금지

public:
	void Render();//UI이미지를 계속 출력하는 부분
	void Update();//계산처리를 계속 갱신하는 부분 
	void Push_Scene(Scene* newScene);//stack 씬을 넣는 함수
	void Pop_Scene();//stack에서 이제 나가는 씬은 없애는 함수
	void Change_Scene(Scene* newScene);//씬을 교체하는 함수

	static SceneManager& getInstance()//씬 매니저를 외부코드에서 사용하고 싶으면 사용하는 함수 (싱글톤)
	{
		static SceneManager instance;
		return instance;
	}

	SceneManager(const SceneManager&) = delete; //복사 방지(싱글톤)
	SceneManager& operator=(const SceneManager&) = delete; //대입 방지 (싱글톤)
};

