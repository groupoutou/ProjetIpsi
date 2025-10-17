#include "Plateau.h"
#include "COUP.h"
#include "Case.h"


#include <iostream>


Case* Plateau::TrouverCase(int i, int j)
{
	 //i pair ?
	if (i % 2 == 0 && j%2 ==0)
			return &data[0]; // case non jouable
	if (i % 2 == 1 && j % 2 == 1)
		return &data[0]; // case non jouable	
	//case or limite
	if (i < 1 || i>10 || j < 1 || j>10)
		return &data[0]; // case non jouable
	int k = 0;
	if (i % 2 == 0)
		k = (i - 1) * 5 + (j / 2) + 1;
	else
		k = (i - 1) * 5 + (j / 2);
	k--;
	return &data[k];
	}



char Plateau::TrouverCouleur(int i, int j) {
	Case c = *(this-> TrouverCase(i, j));
	return c.getCouleur();
}

bool Plateau::aGagner(char couleur) {

	char ennemie;
	if (couleur == 'N') {
		ennemie = 'B';
	}
	else {
		ennemie = 'N';
	}

	int nbPion = 0;
	for (int i = 0; i < 50; i++) {
		if (data[i].getCouleur() == ennemie) {
			nbPion++;
		}
	}
	if (nbPion == 0) {
		return true;
	}
	else {
		return false;
	}
}	

void Plateau::afficher() {

	/*for (int i = 0; i < 50; i++)
	{
		Case c = data[i];
		int x = c.getX();
		int y = c.getY();
		std::cout << "Case " << i << " : (" << x << ", " << y << ") Couleur : " << c.getCouleur() << std::endl;

	}*/

	std::cout << "  1 2 3 4 5 6 7 8 9 10" << std::endl;
	for (int i = 1; i < 11; i++) {
		std::cout << i << " ";
		for (int j = 1; j < 11; j++) {
			if (i % 2 == 0 && j % 2 == 0) {
				std::cout << ". ";
			}
			else if (i % 2 == 1 && j % 2 == 1) {
				std::cout << ". ";
			}
			else {
				char couleur = this->TrouverCouleur(i, j);
				std::cout << couleur << " ";
			}
		}
		std::cout << std::endl;
	}
}

void Plateau::jouercoup(COUP c) {


	//trouver couleur
	int departi, departj;
	departi = c.getDepart().getX();
	departj = c.getDepart().getY();
	char couleurpion = (*this->TrouverCase(departi, departj)).getCouleur();


	//mettre case d'arrivee a la couleur du pion de depart
	int arriveei, arriveej;
	arriveei = c.getArrivee().getX();
	arriveej = c.getArrivee().getY();
	(*this->TrouverCase(arriveei, arriveej)).setCouleur(couleurpion);
	this->afficher();


	
	//mettre case de depart a vide
	(*this->TrouverCase(departi, departj)).detruire();

	//dettruire pion mange
	if (c.getPionCapturer().getCouleur() != ' ') {
		int mangei, mangej;
		mangei = c.getPionCapturer().getX();
		mangej = c.getPionCapturer().getY();
		(*this->TrouverCase(mangei, mangej)).detruire();
	}

	
}

Case  Plateau::getdiag(Case connu, int direction) {

	int x = connu.getX();
	int y = connu.getY();

	if(direction==1)
	return (*this->TrouverCase(x -1, y + 1));
	if (direction == 2)
		return (*this->TrouverCase(x + 1, y + 1));
	if (direction == 3)
		return (*this->TrouverCase(x + 1, y - 1));
	if (direction == 4)
		return (*this->TrouverCase(x - 1, y - 1));
 }

COUP Plateau::peutcapturer(Case depart, int diag) {
	char couleur = depart.getCouleur();
	char ennemie;
	if (couleur == 'N') {
		ennemie = 'B';
	}
	else {
		ennemie = 'N';
	}

	if (depart.getEstDame()) {
		//A IMPLEMENTER PLUS TARD
		return coup_vide;
	}

	Case case1 = this->getdiag(depart, diag);
	Case case2 = this->getdiag(case1, diag);
	if (case1.getCouleur() == ennemie && case2.getCouleur() == ' ') {
		return COUP(depart, case2, case1);
	}
	else {
		return coup_vide;
	}

}

COUP Plateau::peutbouger(Case depart, int diag) {
	char couleur = depart.getCouleur();
	if (!depart.getEstDame())
	{
		if (couleur == 'B' && (diag == 3 || diag == 2)) {
			return coup_vide;
		}
		if (couleur == 'N' && (diag == 1 || diag == 4)) {
			return coup_vide;
		}
		
	}

	if (depart.getEstDame()) {
		//A IMPLEMENTER PLUS TARD
		return coup_vide;
	}

	Case case1 = this->getdiag(depart, diag);
	if (case1.getCouleur() == ' ') {
		return COUP(depart, case1, Case_vide);
	}
	else {
		return coup_vide;
	}

}

void Plateau::AjouterCoup(char couleur) {
	//on vide la liste des coups legaux

	CoupsLegaux.clear();

	//on parcourt le plateau
	for (int i = 0; i < 50; i++)
	{
		Case c = data[i];
		if (c.getCouleur() == couleur) {
			//on regarde si le pion peut capturer
			for (int diag = 1; diag <= 4; diag++) {
				COUP coup = this->peutcapturer(c, diag);
				if (coup.getDepart().getCouleur() != ' ') { //coup non vide 
					CoupsLegaux.push_back(coup);
				}
			}
		}
	}
	if (CoupsLegaux.size() == 0) {
		for (int i = 0; i < 50; i++)
		{
			Case c = data[i];
			//si il ne peut pas capturer on regarde s'il peut bouger
			if (c.getCouleur() == couleur) {
				for (int diag = 1; diag <= 4; diag++) {
					COUP coup = this->peutbouger(c, diag);
					if (coup.getDepart().getCouleur() != ' ') //coup non vide 
						CoupsLegaux.push_back(coup);

				}
			}
		}
	}
}


Plateau::Plateau()
{
	for (int k = 1; k < 51; k++) {


		int i = (k % 5) + 1;
		int j;

		if(i%2==0)
		 j = 2 * (k - (i - 1) * 5);
		else
		 j = 2 * (k - (i * 5));

		i = int((k-1) / 5 + 1);
		j = ((k - 1) % 5) * 2 + (i + 1) % 2 + 2*(i%2);

		if (i <= 4) {
			data[k - 1] = Case(i, j, 'N', false);
		}
		else if (i >= 7) {
			data[k - 1] = Case(i, j, 'B', false);
		}
		else {
			data[k - 1] = Case(i, j, ' ', false);
		}
	
		
	}
	printf("");

}


void Plateau::AfficherCoupsLegaux() {
	for (int i = 0; i < CoupsLegaux.size(); i++) {
		CoupsLegaux[i].afficher();
	}
}