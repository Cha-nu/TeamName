<<<<<<< HEAD
// Ä³¸¯ÅÍ »ý¼º È­¸é.h

#pragma once

// ÀÎÅÍÆäÀÌ½º (ºÎ¸ð Å¬·¡½º)
class CreatingCharacter {
public:
	CreatingCharacter() {} // ±âº» »ý¼ºÀÚ
	virtual ~CreatingCharacter() {} // °¡»ó ¼Ò¸êÀÚ

	// ¼ø¼ö °¡»ó ÇÔ¼ö
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

// ½ÇÁ¦ ½ÃÀÛ È­¸é (ÀÚ½Ä Å¬·¡½º)
class CharacterChoice : public CreatingCharacter {
public:
	CharacterChoice() {} // »ý¼ºÀÚ
	~CharacterChoice() override{} // ºÎ¸ð Å¬·¡½ºÀÇ °¡»ó ¼Ò¸êÀÚ¸¦ override

	// ÇÔ¼ö ÀçÁ¤ÀÇ
=======
ï»¿// ìºë¦­í„° ìƒì„± í™”ë©´.h

#pragma once
#include "../../Scene/Scene.h"

// ì‹¤ì œ ì‹œìž‘ í™”ë©´ (ìžì‹ í´ëž˜ìŠ¤)
class CharacterChoice : public Scene {
public:
	CharacterChoice() {} // ìƒì„±ìž
	~CharacterChoice() override{} // ë¶€ëª¨ í´ëž˜ìŠ¤ì˜ ê°€ìƒ ì†Œë©¸ìžë¥¼ override

	// í•¨ìˆ˜ ìž¬ì •ì˜
>>>>>>> update
	void Init() override;
	void Update() override;
	void Render() override;
	void Exit() override;
};