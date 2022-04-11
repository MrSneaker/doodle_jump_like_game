#include "Jeu.h"

using namespace std;

Jeu::Jeu()
{
}

Jeu::~Jeu()
{
}

const Personnage &Jeu::getConstPersonnage() const
{
	return perso;
}

const Monstre &Jeu::getConstMonstre(int i) const
{
	return monstr[i];
}

vector<Plateforme> Jeu::getPlateforme() const
{
	return p;
}

const bonus &Jeu::getConstBonus(int i) const
{
	return bonu[i];
}

int kbhit()
{
	struct timeval tv;
	fd_set fds;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&fds);
	FD_SET(STDIN_FILENO, &fds); // STDIN_FILENO is 0
	select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &fds);
}

char Jeu::getCh()
{ // lire un caractere si une touche a ete pressee
	char touche = 0;
	if (kbhit())
	{
		touche = fgetc(stdin);
	}

	return touche;
}

bool Jeu::actionClavier(const char touche, double dt)
{
	bool ok = true;
	switch (touche)
	{
	case 'g':
		perso.deplacerG(dt);
		cout << perso.getPos().y;
		break;
		ok = true;
	case 'd':
		perso.deplacerD(dt);
		cout << perso.getPos().y;
		break;
		ok = true;
	case 'r':
		perso.creerProj();
		break;
		ok = true;
	case 'q':
		return ok = false;
		break;
	}
	return ok;
}

void Jeu::actionsAutomatiques(double dt)
{
	for (int i = 0; i < 4; i++)
	{
		if (monstr[i].getTailleM() == 1)
		{
			monstr[i].bougeAuto(dt);
		}
	}
	int a = rand() % p.size();
	p.at(a).bougeAutoLateral(dt);
}

void Jeu::InitPersonnage()
{
	perso.setPos(50, 3);
	perso.setVit(1);
}

void Jeu::InitMonstre()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		monstr[i].setVitM(1);
		monstr[i].setTailleM(1);
		monstr[i].setResistance(1);
		monstr[i].enVie = true;
	}
}

void Jeu::InitBonus()
{
	int i;
	int j = 0;
	for (i = 0; i < 4; i++)
	{

		bonu[i].setDuree(5);
		if (rand() % 100 > 90)
			bonu[i].setNomB("jetpack");
		if (rand() % 100 > 60)
			bonu[i].setNomB("hélice");
		if (rand() % 100 > 25)
			bonu[i].setNomB("ressort");
		if (rand() % 100 > 75)
			bonu[i].setNomB("boing");
		bonu[i].estPris = false;
	}
}

void Jeu::InitPlat()
{
	int i;
	time_t t;
	Plateforme p0(perso.getPos().x + 1, perso.getPos().y, 0, 0, 1, -1);
	p.emplace(p.begin(), p0);
	for (i = 1; i < 12; i++)
	{
		Plateforme tmp;
		tmp.setPos(rand() % 100, rand() % 6);
		if (rand() % 100 <= 70)
			tmp.setRes(-1);
		else
			tmp.setRes(1);
		tmp.setDir(1, 1);
		tmp.setTaille(1);
		if (rand() % 100 > 90)
		{
			bonu[rand() % 4].setPosBonus(tmp.getPos().x - 5, tmp.getPos().y);
		}
		else if (rand() % 100 > 60)
		{
			monstr[rand() % 4].setPos(tmp.getPos().x - 5, tmp.getPos().y);
		}

		p.emplace(p.begin() + i, tmp);
	}
}

void Jeu::updateDefil(double dt)
{
	float vFall = 1;
	float dFall = vFall * dt;
	int compt = 0;
	for (int i = 0; i < p.size(); i++)
	{
		if (perso.getPos().x < 8)
		{
			float x = p.at(i).getPos().x;
			x = x + dFall;
			p.at(i).setPos(x, p.at(i).getPos().y);
		}
		if (p.at(i).getPos().x > 15)
		{
			p.erase(p.begin() + i);
			compt++;
		}
	}
	for (int i = 0; i < compt; i++)
	{
		time_t t;
		srand((unsigned)time(&t));
		Plateforme tmp;
		int x = 0 + rand() % 4;
		tmp.setPos(x, rand() % 19);
		if (rand() % 100 <= 70)
			tmp.setRes(-1);
		else
			tmp.setRes(1);
		tmp.setTaille(1);
		for (int j = 0; j < 4; j++)
		{
			if (rand() % 100 > 90)
			{
				bonu[j].setPosBonus(tmp.getPos().x - 5, tmp.getPos().y);
			}
			else if (rand() % 100 > 60)
			{
				monstr[j].setPos(tmp.getPos().x - 5, tmp.getPos().y);
			}
		}
		p.emplace(p.end() - compt + i, tmp);
	}
}

void Jeu::RecommencerJeu()
{
}

void Jeu::update(double dt)
{
	actionsAutomatiques(dt);
	for (int i = 0; i < p.size(); i++)
	{
		float pposx = p.at(i).getPos().x;
		float pposy = p.at(i).getPos().y;
		if ((perso.getPos().x >= pposx) && (perso.getPos().y >= pposy - 0.1) && (perso.getPos().y <= pposy + 0.1))
		{
			perso.saut(dt);
		}
		else
			perso.tombe(dt);
	}
	for (int i = 0; i < 4; i++)
	{
		if ((perso.getPos().x == monstr[i].getPos().x) && (perso.getPos().y == monstr[i].getPos().y) && (monstr[i].enVie == true))
		{
			perso.tombe(dt);
			perso.enVie = false;
			cout << "mort d'un mob";
		}
		if (perso.getNombreProj() != 0)
		{
			for (int j = 0; j < perso.getNombreProj(); j++)
			{
				if (perso.getProjectile(j).existe == true)
				{
					perso.getProjectile(j).Update(dt);
					if ((perso.getProjectile(j).getpos().x == monstr[i].getPos().x) && (perso.getProjectile(j).getpos().y == monstr[i].getPos().y))
					{
						monstr[i].descRes();
						if (monstr[i].getResistance() == 0)
						{
							monstr[i].enVie = false;
						}
						perso.detruitProj(j);
					}
					if (perso.getProjectile(j).getpos().y >= 20)
					{
						perso.detruitProj(j);
						cout << "lol";
					}
					// cout<<perso.getProjectile(j).getpos().x;
				}
			}
		}
		// updateDefil(dt);
	}
	for (int i = 0; i < 4; i++)
	{
		if ((int(perso.getPos().x) == bonu[i].getPosBonus().x) && (int(perso.getPos().y) == bonu[i].getPosBonus().y))
		{
			std::chrono::high_resolution_clock timer;
			double tps = 0;
			while (tps == bonu[i].getDuree())
			{
				auto start = timer.now();
				if (bonu[i].getNomB() == "jetpack")
					perso.setVit(3);
				else if (bonu[i].getNomB() == "hélice")
					perso.setVit(2);
				else if (bonu[i].getNomB() == "ressort")
					perso.setVit(1.5);
				else if (bonu[i].getNomB() == "boing")
					perso.setVit(1.5);
				auto stop = timer.now();
				tps += std::chrono::duration_cast<std::chrono::duration<double>>(stop - start).count();
				cout << tps;
			}
			bonu[i].estPris = true;
			perso.setVit(1);
		}
	}
	if (perso.getPos().x >= 100)
	{
		perso.enVie = false;
		cout << "mort de chute";
	}
}
