#include "Monster.h"
//#include"Data/ItemKey.h"

//생성자
NormalMonster::NormalMonster(MonsterStat stat) {
	InitializeStat(stat);
	this->droptable = new Inventory();

	//미리 생성자때 포션을 랜덤으로 할당시키기?
	//this->addToDroptable(ItemKey::Health_Potion_Common , 1);//테스트용
}


// 일반몹 드랍테이블 로드
bool NormalMonster::getDropTableFromFile() {
	std::string url = "Monster/Data/NormalDroptable.ini";
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
			//std::cout << id << std::endl;
			std::getline(_tmp , txt , ',');
			count = std::stoi(txt);
			//std::cout << count << std::endl;
			droptable->AddItem(id , count);
		}
		open_file.close();
		return true;
	}
	else {
		return false;
	}
}

// 디버그용

std::ostream& operator<<(std::ostream& os, const NormalMonster& m)
{
    os << "Monster 출력\nName: " << m.stat.name << ", HP: " << m.stat.hp << ", ATK: " << m.stat.atk << ", Type: " << typeid(m).name();
    return os;
}
