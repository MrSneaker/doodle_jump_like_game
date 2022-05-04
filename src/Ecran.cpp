#include "Ecran.h"

int random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
							 // négatif ou positif en fonction des bornes fournies en paramètres.
{
	int res;
	if (max - min < 0)
	{
		res = -1 * (min + rand() % (max - min));
	}
	else
		res = min + rand() % (max - min);

	return res;
}

Ecran::Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p, bonus b[4], Monstre m[4])
{
	debutEcran = posDebut;
	finEcran = posFin;
	nbPlEc = nbPlat;
	Plateforme p0;
	p0.setPos(posDebut - 5, (rand() % 11) + 1);
	for (int i = 0; i < nbPlat; i++)
	{
		int r = rand();
		Plateforme tmp;
		tmp.setPos(random(posFin, posDebut), (r % 11) + 1);
		if (r % 100 <= 70)
			tmp.setRes(-1);
		else
			tmp.setRes(1);
		if (r % 100 > 90)
			tmp.setDir(0, 1);
		if (r % 100 > 95)
			tmp.setDir(1, 0);
		tmp.setTaille(0.7, 2);
		if (r % 100 > 80)
		{
			int bonus = r % NB_BONUS;
			if (b[bonus].disponible)
			{
				b[bonus].setPosBonus(tmp.getPos().x - 5, tmp.getPos().y);
				b[bonus].estPris = false;
				b[bonus].disponible = false;
			}
		}
		else if (r % 100 > 70)
		{
			int monstre = r % NB_MONSTRE;
			if (m[monstre].enVie == false)
			{
				m[monstre].enVie = true;
				m[monstre].setPos(tmp.getPos().x - 5, tmp.getPos().y);
			}
		}
		if (tmp.getPos().x == p0.getPos().x)
		{
			tmp.setPos(tmp.getPos().x - 10, tmp.getPos().y);
		}
		p0 = tmp;
		p.emplace(p.begin(), tmp);
	}
}

int Ecran::getDebutEc() const
{
	return debutEcran;
}

int Ecran::getFinEc() const
{
	return finEcran;
}

void Ecran::detruireEc(vector<Plateforme> &p, bonus b[4], Monstre m[4], int nbPl)
{
	for (int i = 0; i < nbPl; i++)
	{
		p.pop_back();
	}
	for (int i = 0; i < NB_BONUS; i++)
	{
		float posbX = b[i].getPosBonus().x;
		if (posbX < debutEcran && posbX > finEcran)
		{
			b[i].estPris = true;
		}
	}
	for (int i = 0; i < NB_MONSTRE; i++)
	{
		float posmX = m[i].getPos().x;
		if (posmX < debutEcran && posmX > finEcran)
		{
			m[i].enVie = false;
		}
	}
}

int Ecran::getNbPlEc() const
{
	return nbPlEc;
}

Ecran::~Ecran()
{
}