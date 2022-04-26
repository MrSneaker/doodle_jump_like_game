#include "Ecran.h"

Ecran::Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p,bonus b[4], Monstre m[4])
{
    for (int i = 0; i < nbPlat; i++)
	{
		Plateforme tmp;
		tmp.setPos(rand()%100 + posFin, (rand() % 11) + 1);
		if (rand() % 100 <= 70)
			tmp.setRes(-1);
		else
			tmp.setRes(1);
		if (rand() % 100 > 90)
			tmp.setDir(0, 1);
		if (rand() % 100 > 90)
			tmp.setDir(1, 0);
		tmp.setTaille(1, 2);
		if (rand() % 100 > 80)
		{
			int bonus = rand() % 4;
			b[bonus].setPosBonus(tmp.getPos().x - 5, tmp.getPos().y);
			b[bonus].estPris = false;
		}
		else if (rand() % 100 > 70)
		{
			int monstre = rand() % 4;
			cout << "monstre n° : " << monstre;
			m[monstre].enVie = true;
			m[monstre].setPos(tmp.getPos().x - 5, tmp.getPos().y);
		}

		p.push_back(tmp);
	}
}

Ecran::~Ecran()
{
}