#include "Jeu.h"

using namespace std;

float tps = 0;
float camX = 0;

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

const vector<Plateforme> &Jeu::getPlateforme() const
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
	case 'd':
		perso.deplacerD(dt);
		cout << perso.getPos().y;
		break;
	case 'r':
		perso.creerProj(dt);
		break;
	case 'q':
		return false;
		break;
	}
	return ok;
}

void Jeu::actionsAutomatiques(double dt)
{
	for (int i = 0; i < 4; i++)
	{
		if (monstr[i].getTailleM().y == 1) // on fait bouger les monstres de tailles 1/1 uniquement.
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
	camX = perso.getPos().x;
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
		if ((rand() % 100 > 90) && (monstr[i].getTailleM().y == 1))
			monstr[i].setDirM(0, 1);
	}
}

void Jeu::InitBonus()
{
	int i;
	for (i = 0; i < 4; i++)
	{
		bonu[i].setTailleB(1, 1);
		bonu[i].setDuree(0.25);
		if (i == 0)
		{
			bonu[i].setNomB("j");
			bonu[i].setVitB(5);
		}

		if (i == 1)
		{
			bonu[i].setNomB("h");
			bonu[i].setVitB(3);
		}

		if (i == 2)
		{
			bonu[i].setNomB("r");
			bonu[i].setVitB(2);
		}

		if (i == 3)
		{
			bonu[i].setNomB("b");
			bonu[i].setVitB(2);
		}
	}
}

void Jeu::InitPlat() // TODO faire un seul rand
{
	Plateforme p0(perso.getPos().x + 5, perso.getPos().y, 0, 0, 1, 2, -1);
	p.emplace(p.begin(), p0);
	Ecran e1(100, 0, 20, p, bonu, monstr);
	Ecran e2(0, -100, 20, p, bonu, monstr);
	Ecran e3(-100, -200, 20, p, bonu, monstr);
	e.push_back(e1);
	e.push_back(e2);
	e.push_back(e3);
}

void Jeu::updateEcran(double dt)
{
	int debutNewEc = 0;
	int finNewEc = 0;
	for(int i=0;i<e.size();i++)
	{
		bool ecranSuppr = false;
		int dernierSuppr = 0;
		if(perso.getPos().x<e.at(i).getFinEc() - 50)
		{
			e.at(i).detruireEc(p,bonu,monstr,e.at(i).getNbPlEc());
			e.erase(e.begin()+i);
			ecranSuppr = true;
			dernierSuppr = i;
		}
		if(ecranSuppr)
		{
			debutNewEc = e.at(e.size()-1).getFinEc();
			finNewEc = e.at(e.size()-1).getFinEc()-100;
			Ecran tmp(debutNewEc,finNewEc,20,p,bonu,monstr);
			e.push_back(tmp);
		}
		cout <<"dernier ecran suppr : "<< dernierSuppr;
	}
}

void Jeu::RecommencerJeu()
{
}

bool doOverlap(Vec2 l1, Vec2 r1, Vec2 l2, Vec2 r2)
{

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y)
	{
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (r1.y >= l2.y || r2.y >= l1.y)
		return false;

	return true;
}

void Jeu::update(double dt)
{
	cout << "nb plat : " << p.size();
	cout << "nb ecran : "<<e.size();
	for(int i=0;i<p.size();i++)
	{
		//cout<<"position x de p"<<i<<" : "<<p.at(i).getPos().x;
	}
	double px = perso.getPos().x;
	double py = perso.getPos().y;
	double persoSupx = px - perso.getTaille().x;
	double persoSupy = py + perso.getTaille().y;
	Vec2 posperso;
	Vec2 posSupperso;
	posperso.x = px;
	posperso.y = py;
	posSupperso.x = persoSupx;
	posSupperso.y = persoSupy;
	float newcamX = perso.getPos().x + 10;
	if (newcamX < camX)
		camX = newcamX;

	for (long unsigned int i = 0; i < p.size(); i++)
	{
		Vec2 ppos = p.at(i).getPos();
		float pposx = p.at(i).getPos().x;
		float pposy = p.at(i).getPos().y;
		float pSupx = pposx - p.at(i).getTaille().x;
		float pSupy = pposy + p.at(i).getTaille().y;
		Vec2 pposSup;
		pposSup.x = pSupx;
		pposSup.y = pSupy;
		if ((doOverlap(pposSup, ppos, posSupperso, posperso)) && p.at(i).estAfficheable())
		{
			perso.saut(dt);
			if (p.at(i).getRes() != -1 && p.at(i).getRes() != 0)
				p.at(i).descRes();
		}
		else
		{
			perso.tombe(dt);
		}
	}
	if (p.size() == 0)
		perso.tombe(dt);
	if (perso.getNombreProj() > 0)
	{
		for (int j = 0; j < perso.getNombreProj(); j++)
		{
			bool detruit = false;
			if (perso.getProjectile(j).existe == true)
			{
				perso.getProjectile(j).Update(dt);
				if (detruit == false)
				{
					if (((perso.getProjectile(j).getpos().x + 0.2 <= monstr[0].getPos().x) && (perso.getProjectile(j).getpos().x - 0.2 >= monstr[0].getPos().x - monstr[0].getTailleM().x)) && ((perso.getProjectile(j).getpos().y - 0.2 >= monstr[0].getPos().y) && (perso.getProjectile(j).getpos().y + 0.2 <= monstr[0].getPos().y + monstr[0].getTailleM().y)) && (monstr[0].enVie == true))
					{
						perso.detruitProj(j);
						detruit = true;
						monstr[0].descRes();
						if (monstr[0].getResistance() == 0)
						{
							monstr[0].enVie = false;
						}
					}
				}
				if (detruit == false)
				{
					if (((perso.getProjectile(j).getpos().x + 0.2 <= monstr[1].getPos().x) && (perso.getProjectile(j).getpos().x - 0.2 >= monstr[1].getPos().x - monstr[1].getTailleM().x)) && ((perso.getProjectile(j).getpos().y - 0.2 >= monstr[1].getPos().y) && (perso.getProjectile(j).getpos().y + 0.2 <= monstr[1].getPos().y + monstr[1].getTailleM().y)) && (monstr[1].enVie == true))
					{
						perso.detruitProj(j);
						detruit = true;
						monstr[1].descRes();
						if (monstr[1].getResistance() == 0)
						{
							monstr[1].enVie = false;
						}
					}
				}
				if (detruit == false)
				{
					if (((perso.getProjectile(j).getpos().x + 0.2 <= monstr[2].getPos().x) && (perso.getProjectile(j).getpos().x - 0.2 >= monstr[2].getPos().x - monstr[2].getTailleM().x)) && ((perso.getProjectile(j).getpos().y - 0.2 >= monstr[2].getPos().y) && (perso.getProjectile(j).getpos().y + 0.2 <= monstr[2].getPos().y + monstr[2].getTailleM().y)) && (monstr[2].enVie == true))
					{
						perso.detruitProj(j);
						detruit = true;
						monstr[2].descRes();
						if (monstr[2].getResistance() == 0)
						{
							monstr[2].enVie = false;
						}
					}
				}
				if (detruit == false)
				{
					if (((perso.getProjectile(j).getpos().x + 0.2 <= monstr[3].getPos().x) && (perso.getProjectile(j).getpos().x - 0.2 >= monstr[3].getPos().x - monstr[3].getTailleM().x)) && ((perso.getProjectile(j).getpos().y - 0.2 >= monstr[3].getPos().y) && (perso.getProjectile(j).getpos().y + 0.2 <= monstr[3].getPos().y + monstr[3].getTailleM().y)) && (monstr[3].enVie == true))
					{
						perso.detruitProj(j);
						detruit = true;
						monstr[3].descRes();
						if (monstr[3].getResistance() == 0)
						{
							monstr[3].enVie = false;
						}
					}
				}
				if (detruit == false)
				{
					if (perso.getProjectile(j).getpos().x < perso.getPos().x - 100)
					{
						perso.detruitProj(j);
					}
				}
			}
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float mx = monstr[i].getPos().x;
		float my = monstr[i].getPos().y;
		float mxSup = mx - monstr[i].getTailleM().x;
		float mySup = my - monstr[i].getTailleM().y;
		Vec2 monstre;
		Vec2 monstreSup;
		monstre.x = mx;
		monstre.y = my;
		monstreSup.x = mxSup;
		monstreSup.y = mySup;
		if ((((px <= mx) && (px >= mx - monstr[i].getTailleM().x) && (py >= my) && (py <= my + monstr[i].getTailleM().y)) || ((px - perso.getTaille().x <= mx) && (px - perso.getTaille().x >= mx - monstr[i].getTailleM().x) && (py + perso.getTaille().y >= my) && (py + perso.getTaille().y <= my + monstr[i].getTailleM().y))) && (monstr[i].enVie == true))
		{
			//(doOverlap(monstre,monstreSup,posperso,posSupperso) && (monstr[i].enVie == true))
			perso.tombe(dt);
			perso.enVie = false;
			cout << "mort d'un mob";
		}
	}
	for (int i = 0; i < 4; i++)
	{
		float bx = bonu[i].getPosBonus().x;
		float by = bonu[i].getPosBonus().y;
		if ((((px <= bx) && (px >= bx - bonu[i].getTailleB().x) && (py >= by) && (py <= by + bonu[i].getTailleB().y)) || ((px - perso.getTaille().x <= bx) && (px - perso.getTaille().x >= bx - bonu[i].getTailleB().x) && (py + perso.getTaille().y >= by) && (py + perso.getTaille().y <= by + bonu[i].getTailleB().y))) && (bonu[i].estPris == false))
		{
			tps = bonu[i].getDuree();
			bonu[i].estPris = true;
			cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
		}
	}
	for (int i = 0; i < 4; i++)
	{
		if (bonu[i].estPris)
		{
			cout << bonu[i].getNomB() << " est pris";
			if (tps > 0)
			{
				perso.setVit(bonu[i].getVitB());
				perso.saut(dt);
				tps -= dt;
				cout << "temps bonus : " << tps;
			}
			else
			{
				perso.setVit(1);
			}
		}
	}

	if (px >= camX + 55)
	{
		perso.enVie = false;
		cout << "mort de chute";
	}
	actionsAutomatiques(dt);
	updateEcran(dt);
}
