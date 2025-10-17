#pragma once
#include <vector>
#include "coup.h"




class Plateau
{
private :
	Case data[50];
	std::vector<COUP> CoupsLegaux;
public:
	Case* TrouverCase(int i, int j);
	char TrouverCouleur(int i, int j);
	bool aGagner(char couleur);
	void afficher();
	void jouercoup(COUP c);

	Plateau();

	Case  getdiag(Case connu, int direction);
	COUP peutcapturer(Case depart, int diag);
	COUP peutbouger(Case depart, int diag);
	void AjouterCoup(char couleur);
	// to do :  std::vector<COUP> CoupPossible(int index);
	void AfficherCoupsLegaux();
	std::vector<COUP> getCoupsLegaux() { return CoupsLegaux; }

};

