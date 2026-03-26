#pragma once
#include"Scene.h"
class Test_Lobby : public Scene
{
public:
	void Init() override;
	void Render() override;
	void Update() override;
	void Exit() override;
};

