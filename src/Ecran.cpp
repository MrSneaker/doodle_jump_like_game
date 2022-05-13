#include "Ecran.h"

int random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
							 // négatif ou positif en fonction des bornes fournies en paramètres.
{
	int res;
	if (max - min == 0)
		return EXIT_FAILURE;
	if (max - min < 0)
	{
		res = -1 * (min + rand() % (max - min));
	}
	else
		res = min + rand() % (max - min);

	return res;
}

Ecran::Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p, bonus b[4], Monstre m[4], bool genereMB)
{
	debutEcran = posDebut;
	finEcran = posFin;
	nbPlEc = nbPlat;
	Plateforme p0;
	p0.setPos(posDebut, (rand() % 11) + 1);
	for (int i = 0; i < nbPlat; i++)
	{
		int r = rand();
		int r2 = rand();
		Plateforme tmp;										// on créé un tampon..
		float p0X = p0.getPos().x;							// on prend la position vertical de la plateforme i-1..
		tmp.setPos(random(posFin, posDebut), (r % 11) + 1); // on randomise la position de la nouvelle plateforme.
		tmp.posXbase = tmp.getPos().x;						// on garde sa position verticale.
		if (r % 100 < 70) // 70% de chances que la resistance de la plateforme soit infinie.
			tmp.setRes(-1);
		else // 30 qu'elle disparaisse apres un saut.
			tmp.setRes(1);
		if (r2 % 100 > 60) // 40 % de chance qu'elle bouge horizontalement.
			tmp.setDir(0, 1);
		if (r2 % 100 > 90) // 10 % qu'elle bouge verticalement.
			tmp.setDir(4, 0);
		tmp.setTaille(0.7, 2);
		if (genereMB) // si la génération de bonus/monstre est activée..
		{
			if (r % 100 > 80) // pour 20% de chances..
			{
				int bonus = r % NB_BONUS; // sur le bonus tiré..
				if (b[bonus].disponible)  // si celui-ci est disponible..
				{
					if (bonus == 4) // si c'est le trou noir
					{
						b[bonus].setPosBonus(random(posFin, posDebut), (r % 11) + 1); // position random dans l'écran..
						b[bonus].estPris = false;									  // on indique qu'il n'est pas pris.
						b[bonus].disponible = false;								  // on indique qu'il n'est plus disponible.
					}
					else
					{
						b[bonus].setPosBonus(tmp.getPos().x, tmp.getPos().y); // sinon on place le bonus sur la plateforme.
						b[bonus].estPris = false;
						b[bonus].disponible = false;
					}
				}
			}
			else if (r % 100 > 70) // 30% de chance d'avoir un monstre.
			{
				int monstre = r % NB_MONSTRE;
				if (m[monstre].enVie == false) // si le monstre n'est pas en vie..
				{
					m[monstre].enVie = true;						   // on le met en vie.
					m[monstre].setPos(tmp.getPos().x, tmp.getPos().y); // on le met sur la plateforme.
					if (monstre == 0 || monstre == 1)				   // si c'est le monstre n° 0 ou 1..
					{
						if (r2 % 100 > 70) // ..il a 30% de chance de bouger.  
							m[monstre].setDirM(0, 1);
					}
				}
			}
		}

		p0 = tmp; // p0 devient la plateforme que l'on vient de créer.
		p.emplace(p.begin(), tmp); // on rentre p0 dans le tableau dynamique.
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
			b[i].disponible = true;
			b[i].estPris = false;
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