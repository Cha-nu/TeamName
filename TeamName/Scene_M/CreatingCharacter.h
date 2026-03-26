// 캐릭터 생성 화면.h

#pragma once

// 인터페이스 (부모 클래스)
class CreatingCharacter {
public:
	CreatingCharacter() {} // 기본 생성자
	virtual ~CreatingCharacter() {} // 가상 소멸자

	// 순수 가상 함수
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

// 실제 시작 화면 (자식 클래스)
class CharacterChoice : public CreatingCharacter {
public:
	CharacterChoice() {} // 생성자
	~CharacterChoice() override{} // 부모 클래스의 가상 소멸자를 override

	// 함수 재정의
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};