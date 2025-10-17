#pragma once
class Case
{
private :
	int x;
	int y;
	char couleur; // 'N' pour noir, 'B' pour blanc, ' ' pour vide
	bool estDame; // true si le pion est une dame, false sinon
public :
	Case() {
		x = 0;
		y = 0;
		couleur = ' ';
		estDame = false;
	}
	Case(int x, int y, char couleur, bool estDame) {
		this->x = x;
		this->y = y;
		this->couleur = couleur;
		this->estDame = estDame;
	}
	char getCouleur() const { return couleur; }
	bool getEstDame() { return estDame; }
	void setCouleur(char couleur) { this->couleur = couleur; }
	void setEstDame(bool estDame) { this->estDame = estDame; }
	int getX() { return x; }
	int getY() { return y; }
	void setX(int x) { this->x = x; }
	void setY(int y) { this->y = y; }
	void detruire() {
		couleur = ' ';
		estDame = false;
	}
};
#define Case_vide Case(0, 0, ' ', false)
#define Case_invalide Case(-1, -1, 'X', false)

