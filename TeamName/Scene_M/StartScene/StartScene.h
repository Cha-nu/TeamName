<<<<<<< HEAD
// ½ÃÀÛ È­¸é.h

#pragma once

// ÀÎÅÍÆäÀÌ½º (ºÎ¸ð Å¬·¡½º)
class StartScene {
public:
	StartScene() {} // ±âº» »ý¼ºÀÚ
	virtual ~StartScene() {} // °¡»ó ¼Ò¸êÀÚ

	// ¼ø¼ö °¡»ó ÇÔ¼ö
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

// ½ÇÁ¦ ½ÃÀÛ È­¸é (ÀÚ½Ä Å¬·¡½º)
class IntroScene : public StartScene {
public:
	IntroScene() {} // »ý¼ºÀÚ
	~IntroScene() override{} // ºÎ¸ð Å¬·¡½ºÀÇ °¡»ó ¼Ò¸êÀÚ¸¦ override

	// ÇÔ¼ö ÀçÁ¤ÀÇ
=======
ï»¿// ì‹œìž‘ í™”ë©´.h

#pragma once
#include "../../Scene/Scene.h"

// ì‹¤ì œ ì‹œìž‘ í™”ë©´ (ìžì‹ í´ëž˜ìŠ¤)
class StartScene : public Scene {
private:
	int currentIndex = 0; // [0327 ì¶”ê°€] ê²Œìž„ ì‹œìž‘ìš© í™”ì‚´í‘œ
	
public:
	StartScene() {} // ìƒì„±ìž
	~StartScene() override{} // ë¶€ëª¨ í´ëž˜ìŠ¤ì˜ ê°€ìƒ ì†Œë©¸ìžë¥¼ override

	// í•¨ìˆ˜ ìž¬ì •ì˜
>>>>>>> update
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};