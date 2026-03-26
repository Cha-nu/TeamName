
#pragma once
class Scene {
public:
	virtual ~Scene() = default;
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;//보통 BGM일시정지, 행동을 멈추는 기능을 처리하는 부분
};