# TeamName
# 🎮 한국 남자 RPG (Korean Male RPG)

> **"수능부터 취업까지, 한 남자의 치열한 성장 궤적을 그린 텍스트 기반 성장 RPG"** > 본 프로젝트는 C++ 프로그래밍 언어를 기반으로 하며, 객체지향 설계(OOP)를 통해 게임의 각 요소를 모듈화하여 구현한 팀 프로젝트입니다.
<div align="center">
  <img width="710" height="764" alt="image" src="https://github.com/user-attachments/assets/f999f853-db8b-48f1-87be-d9334c872ddd" />
</div>


---

## 🛠 1. 개발 환경 (Development Environment)

* **Language:** C++
* **IDE:** Visual Studio 2022
* **Architecture:** Manager Pattern (Game, Scene, Sound)
* **Target Platform:** Windows Console (x64)

---

## 🌟 2. 주요 시스템 기획 (Game Systems)

### 👤 캐릭터 생성 및 육성
* **커스터마이징:** 이름 지정.
* **스탯 투자:** 레벨업 시(최대 Lv.10) 자동 스탯 상승

### ⚔️ 전투 및 몬스터
* **단계별 성장:** '수능'을 전투로 시작하여 학부 과정의 과목들을 몬스터로 형상화.
* **가변 난이도:** 레벨에 따라 몬스터의 난이도가 실시간으로 변동.
* **학습 몬스터:** C++, 그래픽스 등 실제 전공 과목 기반의 몬스터 데이터 설계.

### 📊 시스템 로그 & UI
키보드 화살표로 게임을 조작, 선택할 수 있습니다.
---

## 🕹 3. 게임 플레이 흐름 (Game Flow)

1.  **Start:** 시작, 불러오기, 환경설정 선택.
2.  **Creation:** 캐릭터 정보 및 특성 설정.
3.  **Main:** 플레이어 스텟확인, 상점 이용, 전공 몬스터와의 전투.
4.  **Final Battle:** 최종 보스 '취업'과의 전투 후 결과(Clear/Over) 출력.

---

## 👥 4. 역할 분담 (Team Roles)

| 이름 | 역할 | 담당 범위 |
| :--- | :--- | :--- |
| **이찬우** | **Game Manager** | 전체 게임 로직 제어 및 시스템 통합 관리 |
| **백무송** | **Scene Manager** | Scene 인터페이스 설계, 씬 전환 및 전투/선택 화면 구현 |
| **이지민** | **Monster** | 몬스터(Monster.h/cpp) 클래스 설계 및 데이터 관리 |
| **양윤성** | **Item / Inventory** | 상점 시스템 및 아이템/인벤토리 로직 구현 |
| **권기문** | **Player** | 플레이어 클래스, 스탯 및 레벨업 시스템 구현 |
| **김민성** | **UI / Scene** | 시작, 생성, 종료 화면 UI 및 로직 구현 |

---

## 📝 5. 조작 방법 및 특징
* **실행:** Build.zip을 압축풀고 TeamName.exe파일을 실행
* **상태 확인:** 게임 중 캐릭터의 현재 스탯과 상태를 확인하고 종료 의사를 결정할 수 있습니다.
* **입력 방식:** 콘솔 기반의 화살표 입력 방식을 지원합니다.
