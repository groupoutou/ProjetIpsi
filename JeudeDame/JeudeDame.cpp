

#include <iostream>
#include "Plateau.h"

int main()
{
	Plateau p = Plateau();
	COUP c;
	int index;
	while (true) {

		p.afficher();
		p.AjouterCoup('B');
		p.AfficherCoupsLegaux();
		std::cout << "entrez l'index du coup a jouer " << std::endl;
		std::cin >> index;
		c = p.getCoupsLegaux()[index];
		p.jouercoup(c);

		p.afficher();
		p.AjouterCoup('N');
		p.AfficherCoupsLegaux();
		std::cout << "entrez l'index du coup a jouer " << std::endl;
		std::cin >> index;
		 c = p.getCoupsLegaux()[index];
		p.jouercoup(c);
	}
	return 0;
  
}


