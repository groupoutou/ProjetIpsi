#pragma once
#include <vector>
#include "coup.h"




class Plateau
{
private :
	Case data[50]; 
	std::vector<COUP> CoupsLegaux;
	Case Case_invalide = Case(-1, -1, 'X', false);
	Case Case_vide = Case(0, 0, ' ', false);
public:
	int TrouverIndex(int i, int j);
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
	std::vector<COUP> CoupPossible(int index,  bool* capture, char couleur);
	void AfficherCoupsLegaux();
	std::vector<COUP> getCoupsLegaux() { return CoupsLegaux; }

	// fonction de test à supprimer après
	void TESTdame();

};

