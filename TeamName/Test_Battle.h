#pragma once
#include"Scene.h"
class Test_Battle :public Scene
{
public:
    void Init() override;
    void Render() override;
    void Update() override;
    void Exit() override;
};

