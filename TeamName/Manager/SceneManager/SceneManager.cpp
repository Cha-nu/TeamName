#include "SceneManager.h"
#include"../../Scene/Scene.h"

void SceneManager::Render()
{
	if ( !SceneStack.empty() )
	{
		SceneStack.top()->Render();
	}
}

void SceneManager::Update()
{
	if ( !SceneStack.empty() )
	{
		SceneStack.top()->Update();
	}
}

void SceneManager::Add_Scene(Scene* newScene)
{
	if ( !SceneStack.empty() ) //비어있지 않다면 현재 씬을 멈추기
	{
		SceneStack.top()->Exit();
	}

	SceneStack.push(newScene);
	SceneStack.top()->Init();
}

void SceneManager::Return_Scene()
{
	if ( !SceneStack.empty() )
	{
		SceneStack.top()->Exit();

		delete SceneStack.top();//동적으로 받은 씬이니까 힙 메모리 해제

		SceneStack.pop();//꺼내야하니까 pop
	}

	//if ( !SceneStack.empty() ) //꺼냈으니 전에 있던 씬을 불러오기
	//{
	//	//SceneStack.top()->Init();//저장되어있던 씬 초기값 호출
	//}
	//else //아예 씬이 없는데 pop을 할려고 하는거라 
	//{
	//	//오류가 나오는 출력 부분 
	//}
}

void SceneManager::Replace_Scene(Scene* newScene)
{
	if ( !SceneStack.empty() )
	{

		SceneStack.top()->Exit();


		delete SceneStack.top();


		SceneStack.pop();
	}

	// 새로운 씬을 부름
	SceneStack.push(newScene);
	SceneStack.top()->Init();
}

void SceneManager::SceneStack_Clear()
{
	while ( !SceneStack.empty() )
	{
		delete SceneStack.top();
		SceneStack.pop();
	}
}

void SceneManager::Set_UseItem_Name(std::string UseItemName)
{
	this->Character_UseItem_Name = UseItemName;
}

std::string SceneManager::Get_UseItem_Name()
{
	return Character_UseItem_Name;
}
