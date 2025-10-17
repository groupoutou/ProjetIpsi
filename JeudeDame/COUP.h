#pragma once
#include "Case.h"
#include <iostream>
class COUP
{
private :
	//test pour git 
	Case depart;
	Case arrivee;
	Case pionCapturer;
public:
	COUP() {
		depart = Case(0, 0, ' ', false);
		arrivee = Case(0, 0, ' ', false);
		pionCapturer = Case(0, 0, ' ', false);
	}
	COUP(Case depart, Case arrivee, Case pionCapturer) {
		this->depart = depart;
		this->arrivee = arrivee;
		this->pionCapturer = pionCapturer;
	}
	Case getDepart() { return depart; }
	Case getArrivee() { return arrivee; }
	Case getPionCapturer() { return pionCapturer; }
	void setDepart(Case depart) { this->depart = depart; }
	void setArrivee(Case arrivee) { this->arrivee = arrivee; }
	void setPionCapturer(Case pionCapturer) { this->pionCapturer = pionCapturer; }	
	void afficher() {
		std::cout << "Depart : (" << depart.getX() << ", " << depart.getY() << ") ";
		std::cout << "Arrivee : (" << arrivee.getX() << ", " << arrivee.getY() << ") ";
		std::cout << "Pion Capturer : (" << pionCapturer.getX() << ", " << pionCapturer.getY() << ")" << std::endl;
	}

};

#define coup_vide COUP(Case(0, 0, ' ', false), Case(0, 0, ' ', false), Case(0, 0, ' ', false))