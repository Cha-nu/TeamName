<<<<<<< HEAD
// Á¾·á È­¸é.h

#pragma once

// ÀÎÅÍÆäÀÌ½º (ºÎ¸ð Å¬·¡½º)
class EndScene {
public:
	EndScene() {} // ±âº» »ý¼ºÀÚ
	virtual ~EndScene(){} // °¡»ó ¼Ò¸êÀÚ

	// ¼ø¼ö °¡»ó ÇÔ¼ö
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

// ½ÇÁ¦ Á¾·á È­¸é (ÀÚ½Ä Å¬·¡½º)
class GameOverScene : public EndScene {
public:
	GameOverScene(){} // »ý¼ºÀÚ
	~GameOverScene() override{} // ºÎ¸ð Å¬·¡½ºÀÇ °¡»ó ¼Ò¸êÀÚ¸¦ override

	// ÇÔ¼ö ÀçÁ¤ÀÇ
=======
ï»¿// ì¢…ë£Œ í™”ë©´.h

#pragma once
#include "../../Scene/Scene.h"

// ì‹¤ì œ ì¢…ë£Œ í™”ë©´ (ìžì‹ í´ëž˜ìŠ¤)
class GameOverScene : public Scene {
private:
	int currentIndex = 0; // [0327 ì¶”ê°€] ê²Œìž„ ì‹œìž‘ìš© í™”ì‚´í‘œ
public:
	GameOverScene(){} // ìƒì„±ìž
	~GameOverScene() override{} // ë¶€ëª¨ í´ëž˜ìŠ¤ì˜ ê°€ìƒ ì†Œë©¸ìžë¥¼ override

	// í•¨ìˆ˜ ìž¬ì •ì˜
>>>>>>> update
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};