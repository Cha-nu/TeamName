#include "BossMonster.h"

BossMonster::BossMonster(MonsterStat stat) {
	InitializeStat(stat);
	initializeIntro();
}

//등장 대사 초기화 
void BossMonster::initializeIntro(std::string dialog) {
	this->dialogue = dialog;
}

// 보스몹 드랍테이블 로드
bool BossMonster::getDropTableFromFile() {
	std::string url = "Monster/Data/BossDroptable.ini";
	std::string txt;
	std::string id;
	int count;
	std::fstream open_file(url);

	if ( open_file.is_open() ) {
		char bom[3];
		open_file.read(bom , 3);
		if ( !((unsigned char)bom[0] == 0xEF &&
			(unsigned char)bom[1] == 0xBB &&
			(unsigned char)bom[2] == 0xBF) ) {
			open_file.seekg(0);
		}
		while ( std::getline(open_file , txt) ) {
			if ( txt.empty() || txt[0] == '/' && txt[1] == '/' ) {
				continue;
			}
			std::stringstream _tmp = std::stringstream(txt);
			std::getline(_tmp , id , ',');
			std::cout << id << std::endl;
			std::getline(_tmp , txt , ',');
			count = std::stoi(txt);
			std::cout << count << std::endl;
			droptable->AddItem(id , count);
		}
		open_file.close();
		return true;
	}
	else {
		return false;
	}	
}

//등장 대사 return
std::string BossMonster::introMonster() {
	std::string intro;
	intro = this->dialogue;	
	intro.append("\n보스 몬스터 ");
	intro.append(this->stat.name);
	intro.append(" (이)가 등장했습니다.");
	return intro;
}

// 디버그용

std::ostream& operator<<(std::ostream& os , const BossMonster& m)
{
	os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name() << "\nIntro: " << m.dialogue;
	return os;
}
