#include "Ecran.h"

int random(int min, int max) // fonction permettant de renvoyer un nombre aléatoire
							 // négatif ou positif en fonction des bornes fournies en paramètres.
{
	int res;
	if (max - min == 0) // pour éviter les erreurs fatales du à un modulo 0.
		return EXIT_FAILURE;
	if (max - min < 0)
	{
		res = -1 * (min + rand() % (max - min));
	}
	else
		res = min + rand() % (max - min);

	return res;
}

Ecran::Ecran(int posDebut, int posFin, int nbPlat, vector<Plateforme> &p, bonus b[4], Monstre m[4], bool genereMB, int scoreJeu)
{
	debutEcran = posDebut;
	finEcran = posFin;
	int difficult = scoreJeu / 1000;
	nbPlEc = nbPlat - difficult; // on ajuste le nombre de plateforme en fonction du score.
	if (nbPlEc < 15)			 // si il passe en dessous de 15, on le maintient.
		nbPlEc = 15;
	Plateforme p0;
	p0.setPos(posDebut, (rand() % 11) + 1);
	for (int i = 0; i < nbPlEc; i++)
	{
		int r = rand();
		int r2 = rand();
		Plateforme tmp;										// on créé un tampon..
		tmp.setPos(random(posFin, posDebut), (r % 11) + 1); // on randomise la position de la nouvelle plateforme.
		tmp.posXbase = tmp.getPos().x;						// on garde sa position verticale à la génération (pour l'intervalle de déplacement auto en vertical).
		if (r % 100 < 70 - difficult)						// 70% de chances que la resistance de la plateforme soit infinie. Ajustée en fonction du score (comme tout les pourcentages si dessous).
			tmp.setRes(-1);
		else // 30 qu'elle disparaisse apres un saut.
			tmp.setRes(1);
		if (r2 % 100 > 60 - difficult) // 40 % de chance qu'elle bouge horizontalement.
			tmp.setDir(0, 1);
		if (r2 % 100 > 90 - difficult) // 10 % qu'elle bouge verticalement.
			tmp.setDir(4, 0);
		tmp.setTaille(0.7, 2);
		if (genereMB) // si la génération de bonus/monstre est activée..
		{
			if (r % 100 > 80 - difficult) // pour 20% de chances..
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
			else if (r % 100 > 70 - difficult) // 30% de chance d'avoir un monstre.
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

		p0 = tmp;				   // p0 devient la plateforme que l'on vient de créer.
		p.emplace(p.begin(), tmp); // on rentre la nouvelle plateforme dans le tableau dynamique en tête de celui-ci (car on supprimera en queue).
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
	for (int i = 0; i < nbPl; i++) // on supprime toutes les plateformes situées en queue.
	{
		p.pop_back();
	}
	for (int i = 0; i < NB_BONUS; i++) // si des bonus subsitent, on les rend disponible à la nouvelle génération.
	{
		float posbX = b[i].getPosBonus().x;
		if (posbX < debutEcran && posbX > finEcran)
		{
			b[i].disponible = true;
			b[i].estPris = false;
		}
	}
	for (int i = 0; i < NB_MONSTRE; i++)// de même pour les monstres.
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