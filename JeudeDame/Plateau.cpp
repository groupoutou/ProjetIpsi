#include "Plateau.h"
#include "COUP.h"
#include "Case.h"


#include <iostream>


Case* Plateau::TrouverCase(int i, int j)
{
	 //i pair ?
	if (i % 2 == 0 && j%2 ==0)
			return &Case_invalide; // case non jouable
	if (i % 2 == 1 && j % 2 == 1)
		return &Case_invalide; // case non jouable	
	//case hors limite
	if (i < 1 || i>10 || j < 1 || j>10)
		return &Case_invalide; // case non jouable
	int k = 0;

	if (i % 2 == 0)
		k = (i - 1) * 5 + (j / 2) + 1;
	else
		k = (i - 1) * 5 + (j / 2);
	k--;
	return &data[k];
	}

int Plateau::TrouverIndex(int i, int j) {
	int k = 0;
	if (i % 2 == 0)
		k = (i - 1) * 5 + (j / 2) + 1;
	else
		k = (i - 1) * 5 + (j / 2);
	k--;
	return k;
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
	bool capture = false;

	//on parcourt le plateau
	std::vector<COUP> couppossible;
	for (int i = 0; i < 50; i++)
	{
		couppossible.clear();
		bool old = capture;
		couppossible = this->CoupPossible(i, &capture, couleur);
		if (old != capture) // si capture est passé a true
			CoupsLegaux.clear();
		CoupsLegaux.insert(CoupsLegaux.end(), couppossible.begin(), couppossible.end());
		
	}
}

std::vector<COUP> Plateau::CoupPossible(int index, bool* capture,char couleur) {

	Case c = this->data[index];
	std::vector<COUP> listecoup;
	listecoup.clear();
	if (c.getCouleur() == couleur) {
		if (c.getEstDame())
		{
			//on parcours les 4 diagonales
			Case current = c;
			for (int diag = 1; diag <= 4; diag++) {
				std::vector<Case> suitediag;
				int num = 0;
				while (true) {
					Case next = this->getdiag(current, diag);
					if (next.getCouleur() == 'X')  //case invalide 
						break;
					else {
						suitediag.push_back(next);
						current = next;
					}
					num++;
				}

				int nombreDepionManger = 0;
				Case capturer = Case_vide;
				//on parcours la diagonale
				for (int k = 1; k < num; k++) {
					Case test = suitediag[k];
					if (test.getCouleur() == ' ') {
						if (nombreDepionManger == 1) {
							//on ajoute le coup de capture
							COUP coup = COUP(c, test, capturer);
							listecoup.push_back(coup);
							*capture = true;
						}
						else if (nombreDepionManger == 0 && not(*capture)) {
							//on ajoute le coup de deplacement
							COUP coup = COUP(c, test, Case_vide);
							listecoup.push_back(coup);
						}
					}
					else if (test.getCouleur() != couleur && test.getCouleur() != ' ') {
						nombreDepionManger++;
						capturer = test;
						if (nombreDepionManger > 1) {
							break; //plus d'une piece ennemie sur la diagonale
						}
					}
					else if (test.getCouleur() == couleur) {
						break; //une piece amie bloque la diagonale
					}
				}	
			}	
	
		}

		else {
			
		//on regarde si le pion peut capturer
		for (int diag = 1; diag <= 4; diag++) {
			COUP coup = this->peutcapturer(c, diag);
			if (coup.getDepart().getCouleur() != ' ') { //coup non vide 
					listecoup.push_back(coup);
					*capture = true;
			}
		}
		if (not(*capture)) {
		//si il ne peut pas capturer on regarde s'il peut bouger
			for (int diag = 1; diag <= 4; diag++) {
					COUP coup = this->peutbouger(c, diag);
					if (coup.getDepart().getCouleur() != ' ') //coup non vide 
						listecoup.push_back(coup);
			}
		}	
			
		}
	}
	return listecoup;
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


void Plateau::TESTdame() {
	//reset le plateau
	for (int k = 0; k < 50; k++) {
		this->data[k].setCouleur(' ');
	}
	//placer une dame noire en 5,5
	this->data[this->TrouverIndex(5, 5)].setCouleur('N');
	this->data[this->TrouverIndex(5, 5)].setEstDame(true);
	//placer des pions blancs
	this->data[this->TrouverIndex(4, 6)].setCouleur('B');


}