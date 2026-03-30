////Monster 디버그용
//#include <string>
//#include "Monster.h"
//#include "BossMonster.h"
//
//int main(void) {
//	NormalMonster* monster2 = new NormalMonster();
//	BossMonster* monster3 = new BossMonster();
//	monster2->addToDroptable("Health_Potion_Common" , 2);
//	monster2->removeToDroptable("Health_Potion_Common" , 1);
//	monster2->addToDroptable("Health_Potion_Rare" , 1);
//	for ( int i = 0; i < 100; i++ ) {
//		std::cout << monster2->getDropGold() << std::endl;
//		std::cout << monster3->getDropGold() << "\n" << std::endl;
//	}
//
//	//std::cout << monster2->getDropItem().GetItem()->GetName() << std::endl;
//	if ( monster2->getDropItem().GetItem() != nullptr ) {
//		std::cout << monster2->getDropItem().GetItem()->GetName();
//	}
//}
//
//	//Player* player = new Player("abc");
//	//std::cout << *monster2 << std::endl;
//	//std::cout << *monster3 << std::endl;
//	//std::cout << "\n\n\n" << std::endl;
//
//
//	//monster2->introMonster();
// //   while (!monster2->isDead()) {
//	//	monster2->attackPlayer(player);
//	//	player->ShowPlayerStat();
//	//	player->Attack(monster2);
// //   }
//
//	//std::cout << "\n\n\n" << std::endl;
//
//	//monster3->introMonster();
//	//while (!monster3->isDead()) {
//	//	monster3->attackPlayer(player);
//	//	player->ShowPlayerStat();
//	//	player->Attack(monster3);
//	//}
//
//	//delete player;
// //   delete monster2;
//	//delete monster3;
////    return 0;
////}