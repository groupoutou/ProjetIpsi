

#include <iostream>
#include "Plateau.h"

int main()
{
	Plateau p = Plateau();
	COUP c;
	int index;

	p.TESTdame();
	while (true) {

		p.afficher();
		p.AjouterCoup('B');
		p.AfficherCoupsLegaux();
		std::cout << "entrez l'index du coup a jouer " << std::endl;
		std::cin >> index;
		c = p.getCoupsLegaux()[index];
		p.jouercoup(c);
		if (p.aGagner('B')) {
			std::cout << "Les blancs ont gagne !" << std::endl;
			break;
		}

		p.afficher();
		p.AjouterCoup('N');
		p.AfficherCoupsLegaux();
		std::cout << "entrez l'index du coup a jouer " << std::endl;
		std::cin >> index;
		c = p.getCoupsLegaux()[index];
		p.jouercoup(c);
		if (p.aGagner('N')) {
			std::cout << "Les noirs ont gagne !" << std::endl;
			break;
		}
	}
	return 0;
  
}


