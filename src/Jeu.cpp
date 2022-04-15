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
		perso.creerProj(dt);
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
		if (monstr[i].getTailleM().y == 1)
		{
			monstr[i].bougeAuto(dt);
		}
	}
	for (long unsigned int i = 0; i < p.size(); i++)
		p.at(i).bougeAutoLateral(dt);
}

void Jeu::InitPersonnage()
{
	perso.setPos(50, 6);
	perso.setVit(1);
}

void Jeu::InitMonstre()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		monstr[i].setVitM(1);
		monstr[i].setTailleM((rand() % 1) + 1, (rand() % 1) + 1);
		if (monstr[i].getTailleM().y == 2)
			monstr[i].setResistance(2);
		else
			monstr[i].setResistance(1);
		if ((rand() % 100 > 60) && (monstr[i].getTailleM().y == 1))
			monstr[i].setDirM(0, 1);
	}
}

void Jeu::InitBonus()
{
	int i;
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
	}
}

void Jeu::InitPlat()
{
	int i;
	Plateforme p0(perso.getPos().x + 1, perso.getPos().y, 0, 0, 1, 2, -1);
	p.emplace(p.begin(), p0);
	for (i = 1; i < 12; i++)
	{
		Plateforme tmp;
		tmp.setPos((rand() % 99) + 1, (rand() % 11) + 1);
		if (rand() % 100 <= 70)
			tmp.setRes(-1);
		else
			tmp.setRes(1);
		if (rand() % 100 > 90)
			tmp.setDir(0, 1);
		if (rand() % 100 > 90)
			tmp.setDir(1, 0);
		tmp.setTaille(1, 2);
		if (rand() % 100 > 90)
		{
			int b = rand() % 4;
			bonu[b].setPosBonus(tmp.getPos().x - 5, tmp.getPos().y);
			bonu[b].estPris = false;
		}
		else if (rand() % 100 > 70)
		{
			int m = rand() % 4;
			cout << "monstre n° : " << m;
			monstr[m].enVie = true;
			monstr[m].setPos(tmp.getPos().x - 5, tmp.getPos().y);
		}

		p.emplace(p.begin() + i, tmp);
	}
}

void Jeu::updateDefil(double dt)
{
	float vFall = 1;
	float dFall = vFall * dt;
	int compt = 0;
	for (long unsigned int i = 0; i < p.size(); i++)
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
		tmp.setTaille(1, 2);
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
	float px = perso.getPos().x;
	float py = perso.getPos().y;

	for (long unsigned int i = 0; i < p.size(); i++)
	{
		float pposx = p.at(i).getPos().x;
		float pposy = p.at(i).getPos().y;
		float pSupx = pposx - p.at(i).getTaille().x;
		float pSupy = pposy + p.at(i).getTaille().y;
		if (((px <= pposx) && (px >= pSupx)) && ((((py >= pposy) && (py <= pSupy))) || (((py + perso.getTaille().y >= pposy) && (py + perso.getTaille().y <= pSupy)))))
		{
			perso.saut(dt);
		}
		else
			perso.tombe(dt);
	}
	for (int j = 0; j < perso.getNombreProj(); j++)
	{
		if (perso.getProjectile(j).existe == true)
		{
			perso.getProjectile(j).Update(dt);
			for (int i = 0; i < 4; i++)
			{
				cout<<" j = "<<j;
				if (((perso.getProjectile(j).getpos().x <= monstr[i].getPos().x) && (perso.getProjectile(j).getpos().x >= monstr[i].getPos().x - monstr[i].getTailleM().x)) && ((perso.getProjectile(j).getpos().y >= monstr[i].getPos().y) && (perso.getProjectile(j).getpos().y <= monstr[i].getPos().y + monstr[i].getTailleM().y)))
				{
					cout<<" j à détruire = "<<j;
					cout << "alo?????";
					perso.detruitProj(j);
					monstr[i].descRes();
					if (monstr[i].getResistance() == 0)
					{
						monstr[i].enVie = false;
					}
				}
			}
			if (perso.getProjectile(j).getpos().x < -5)
			{
				perso.detruitProj(j);
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float mx = monstr[i].getPos().x;
		float my = monstr[i].getPos().y;
		if ((((px <= mx) && (px >= mx - monstr[i].getTailleM().x) && (py >= my) && (py <= my + monstr[i].getTailleM().y)) || ((px - perso.getTaille().x <= mx) && (px - perso.getTaille().x >= mx - monstr[i].getTailleM().x) && (py + perso.getTaille().y >= my) && (py + perso.getTaille().y <= my + monstr[i].getTailleM().y))) && (monstr[i].enVie == true))
		{
			perso.tombe(dt);
			perso.enVie = false;
			cout << "mort d'un mob";
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if ((int(px) == bonu[i].getPosBonus().x) && (int(py) == bonu[i].getPosBonus().y))
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
	if (px >= 100)
	{
		perso.enVie = false;
		cout << "mort de chute";
	}
	actionsAutomatiques(dt);
}
