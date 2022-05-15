#include "Jeu.h"

using namespace std;

Jeu::Jeu()
{
	Init();
	Ptombe = true;
	Psaute = false;
	Pdroite = false;
	Pgauche = false;
	Ptire = false;
	PcollPl = false;
	Mtouche1 = false;
	Mtouche2 = false;
	score = 0;
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

bool Jeu::actionClavier(const char touche, double dt)
{
	bool ok = true;
	switch (touche)
	{
	case 'g':
		perso.deplacerG(dt);
		Pgauche = true;
		Pdroite = false;
		Ptire = false;
		break;
	case 'd':
		perso.deplacerD(dt);
		Pgauche = false;
		Pdroite = true;
		Ptire = false;
		break;
	case 'r':
		perso.creerProj(dt);
		Pgauche = false;
		Pdroite = false;
		Ptire = true;
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
		monstr[i].bougeAuto(dt);
	}
	for (long unsigned int i = 0; i < p.size(); i++)
		p.at(i).bougeAuto(dt);
}

void Jeu::InitPersonnage()
{
	perso.setPos(90, 6); // personnage innitialisé au milieu de l'écran en horizontal, en bas de celui-ci.
	perso.setVit(1, 1);
	camX = perso.getPos().x;
}

void Jeu::InitMonstre()
{
	int i;
	int r = rand() % 100;
	for (i = 0; i < NB_MONSTRE; i++)
	{
		monstr[i].setVitM(1);
		if (i == 0)
		{
			monstr[i].setTailleM(1, 2);
			monstr[i].setResistance(1);
			if (r > 70)
				monstr[i].setDirM(0, 1);
		}
		if (i == 1)
		{
			monstr[i].setTailleM(1, 1);
			monstr[i].setResistance(1);
			if (r > 70)
				monstr[i].setDirM(0, 1);
		}
		if (i == 2)
		{
			monstr[i].setTailleM(1.5, 1);
			monstr[i].setResistance(2);
		}
		if (i == 3)
		{
			monstr[i].setTailleM(0.7, 2);
			monstr[i].setResistance(2);
		}
	}
}

void Jeu::InitBonus()
{
	int i;
	for (i = 0; i < NB_BONUS; i++)
	{

		if (i == 0)
		{
			bonu[i].setDuree(10);
			bonu[i].setTailleB(2, 1);
			bonu[i].setNomB("j");
			bonu[i].setVitB(3.5);
		}

		if (i == 1)
		{
			bonu[i].setDuree(10);
			bonu[i].setTailleB(1, 1);
			bonu[i].setNomB("h");
			bonu[i].setVitB(0.8);
		}

		if (i == 2)
		{
			bonu[i].setDuree(0.5);
			bonu[i].setTailleB(1, 1);
			bonu[i].setNomB("r");
			bonu[i].setVitB(5);
		}

		if (i == 3)
		{
			bonu[i].setDuree(5);
			bonu[i].setTailleB(1, 1);
			bonu[i].setNomB("b");
			bonu[i].setVitB(2);
		}
		if (i == 4)
		{
			bonu[i].setDuree(0.25);
			bonu[i].setTailleB(2, 2);
			bonu[i].setNomB("t");
		}
	}
}

void Jeu::InitEc() // on joue avec trois écran générés à la fois.
{
	Plateforme p0(perso.getPos().x + 5, perso.getPos().y, 0, 0, 0.7, 2, -1);
	p.emplace(p.begin(), p0);
	Ecran e1(100, 0, 20, p, bonu, monstr, false, 0);
	Ecran e2(0, -100, 20, p, bonu, monstr, true, 0);
	Ecran e3(-100, -200, 20, p, bonu, monstr, true, 0);
	e.push_back(e1);
	e.push_back(e2);
	e.push_back(e3);
}

void Jeu::updateEcran(double dt)
{
	int debutNewEc = 0;
	int finNewEc = 0;
	for (long unsigned int i = 0; i < e.size(); i++)
	{
		bool ecranSuppr = false;
		if (perso.getPos().x < e.at(i).getFinEc() - 50) // si on dépasse l'écran..
		{
			e.at(i).detruireEc(p, bonu, monstr, e.at(i).getNbPlEc()); // on appel la fonction de destruction..
			e.erase(e.begin() + i);									  // on le supprime du tableau dynamique..
			ecranSuppr = true;										  //.. et on indique qu'un écran vient d'être supprimé.
		}
		if (ecranSuppr) // si l'écran est supprimé..
		{
			debutNewEc = e.at(e.size() - 1).getFinEc();						   // on construit un nouvel écran depuis la fin de l'ancien..
			finNewEc = e.at(e.size() - 1).getFinEc() - 100;					   // on calcul sa position de fin..
			Ecran tmp(debutNewEc, finNewEc, 20, p, bonu, monstr, true, score); //.. on appel le constructeur.
			e.push_back(tmp);
		}
	}
}

bool doOverlap(Vec2 l1, Vec2 r1, Vec2 l2, Vec2 r2) // fonction vérifiant si deux rectangles en paramètres se superposent.
{

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x || l2.y == r2.y)
	{
		return false;
	}

	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	if (r1.y >= l2.y || r2.y >= l1.y)
		return false;

	return true;
}

Ecran Jeu::locEc()
{
	int numEc = 0;
	for (long unsigned int i = 0; i < e.size(); i++)
	{
		if (camX > e.at(i).getFinEc() && camX < e.at(i).getDebutEc())
		{
			numEc = i;
		}
	}
	return e.at(numEc);
}

void Jeu::Init()
{
	InitPersonnage();
	InitBonus();
	InitMonstre();
	InitEc();
}

void Jeu::update(double dt)
{
	double px = perso.getPos().x; // on prend la position du personnage basse..
	double py = perso.getPos().y;
	double persoSupx = px - perso.getTaille().x; // ..et haute (i.e coins bas et coins haut de celui ci)
	double persoSupy = py + perso.getTaille().y;
	Vec2 posperso;
	Vec2 posSupperso;
	posperso.x = px;
	posperso.y = py;
	posSupperso.x = persoSupx;
	posSupperso.y = persoSupy;
	float newcamX = perso.getPos().x + 10;
	if (newcamX < camX) // définition de la position de la caméra.
	{
		camX = newcamX;
		if (camX > 0) // le score augmente si le joueur monte, donc si la caméra monte.
			score += camX / 100;
		else // comme on monte dans les négatifs, on prend l'opposé.
			score += (-1 * camX) / 100;
	}

	for (long unsigned int i = 0; i < p.size(); i++) // on vérifie pour chaque plateforme.
	{
		Vec2 ppos = p.at(i).getPos();
		float pposx = p.at(i).getPos().x - 10; // on décale pour que le personnage saute au niveau de ses pieds.
		float pposy = p.at(i).getPos().y;
		float pSupx = pposx - p.at(i).getTaille().x;
		float pSupy = pposy + p.at(i).getTaille().y;
		Vec2 pposSup;
		pposSup.x = pSupx;
		pposSup.y = pSupy;
		bool collisionPlat = (doOverlap(pposSup, ppos, posSupperso, posperso)) && p.at(i).estAfficheable(); // on rentre en collision si la plateforme est toujours là.
		if (collisionPlat && Ptombe && !perso.aPrisB && perso.enVie)
		{
			tpsSaut = 35;	// duree du saut.
			Psaute = true;	// on peut sauter..
			Ptombe = false; // .. mais pas tomber.
			if (p.at(i).getRes() != -1 && p.at(i).getRes() != 0)
				p.at(i).descRes();
		}
		if (tpsSaut > 0 && Psaute)
		{
			perso.saut(dt);
			tpsSaut -= dt;
		}
		else if (!perso.aPrisB) // si le perso n'est pas avec un bonus.
		{
			Psaute = false; // on ne saute plus..
			Ptombe = true;	//.. donc on tombe.
			perso.tombe(dt);
		}
		if (tpsSaut >= 34)
			PcollPl = true; // on est en collision avec la plateforme (pour le bruit de saut).
		else
			PcollPl = false;
	}
	if (p.size() == 0) // si il n'y a pas de plateformes, on tombe (pour éviter les blocages en cas de bug).
		perso.tombe(dt);
	if (perso.getNombreProj() > 0) // si le nombre de projectiles n'est pas nul.
	{
		for (int i = 0; i < NB_MONSTRE; i++) // pour tous les monstres..
		{
			float mx = monstr[i].getPos().x;
			float my = monstr[i].getPos().y;
			float mxSup = mx - monstr[i].getTailleM().x;
			float mySup = my + monstr[i].getTailleM().y;
			Vec2 monstre;
			Vec2 monstreSup;
			monstre.x = mx;
			monstre.y = my;
			monstreSup.x = mxSup;
			monstreSup.y = mySup;
			for (int j = 0; j < perso.getNombreProj(); j++) // pour tous les projectiles..
			{
				float projX = perso.getProjectile(j).getpos().x;
				float projY = perso.getProjectile(j).getpos().y;
				Vec2 proj;
				Vec2 projRadius;
				proj.x = projX;
				proj.y = projY;
				projRadius.x = projX - 1;
				projRadius.y = projY + 1;
				bool detruit = false;
				if (perso.getProjectile(j).existe == true) // si le projectile existe..
				{
					perso.getProjectile(j).Update(dt); // on le fait avancer..
					if (detruit == false)			   // si il n'est pas déjà détruit..
					{
						if (doOverlap(projRadius, proj, monstreSup, monstre) && (monstr[i].enVie == true)) //.. et qu'il rentre en collision avec un monstre..
						{
							perso.detruitProj(j); // on détruit le projectile..
							detruit = true;		  // on l'indique..
							monstr[i].descRes();  // monstre perd une vie..
							score += 500;
							Mtouche1 = true; // on indique pour le son qu'on a touché le monstre une fois.
							break;			 // on sort de la boucle, car le projectile n'existe plus.
						}
					}
					if (detruit == false) // si le projectile n'est toujours pas
					{
						if (perso.getProjectile(j).getpos().x < perso.getPos().x - 100) // on le détruit si il dépasse 100 au dessus de nous.
						{
							perso.detruitProj(j);
						}
					}
				}
			}
			if (monstr[i].getResistance() == 0) // si plus de vie, monstre mort.
			{
				monstr[i].enVie = false;
			}
		}
	}

	for (int i = 0; i < NB_MONSTRE; i++) // pour tous les monstres.. (boucle sur les collisions avec le perso)
	{
		float mx = monstr[i].getPos().x;
		float my = monstr[i].getPos().y;
		float mxSup = mx - monstr[i].getTailleM().x;
		float mySup = my + monstr[i].getTailleM().y;
		Vec2 monstre;
		Vec2 monstreSup;
		monstre.x = mx;
		monstre.y = my;
		monstreSup.x = mxSup;
		monstreSup.y = mySup;
		bool collisionM = doOverlap(monstreSup, monstre, posSupperso, posperso) && (monstr[i].enVie == true);
		if (collisionM && !perso.aPrisB) // si le personnage n'a pas de bonus, et si le monstre est en vie..
		{								 // on rentre en collision.
			if (Ptombe && perso.enVie)	 // si le personnage est entrain de tomber
			{
				tpsSaut = 35; // on saute..
				Psaute = true;
				Ptombe = false;
				monstr[i].enVie = false; // et le monstre meurt..
				Mtouche2 = true;		 // on joue le son quand on touche un monstre.
				score += 1000;
			}
			else if (!Ptombe) // sinon, on meurt.
			{
				perso.tombe(dt);
				perso.enVie = false;
			}
		}
		if (monstr[i].getResistance() == 0) // si le monstre n'a plus de resistance..
		{
			monstr[i].enVie = false; // il meurt.
		}
	}
	for (int i = 0; i < NB_BONUS; i++) // pour tous les bonus.
	{
		float bx = bonu[i].getPosBonus().x;
		float by = bonu[i].getPosBonus().y;
		float bSupx = bx - bonu[i].getTailleB().x;
		float bSupy = by + bonu[i].getTailleB().y;
		Vec2 bonus;
		Vec2 bonusSup;
		bonus.x = bx;
		bonus.y = by;
		bonusSup.x = bSupx;
		bonusSup.y = bSupy;
		bool collisionB = doOverlap(bonusSup, bonus, posSupperso, posperso) && !bonu[i].estPris && !perso.aPrisB;
		if (collisionB && perso.enVie) // si le personnage n'a pas déjà un bonus et que le bonus n'a pas déjà été pris et qu'il est vivant..
		{							   // on peut rentrer en collision.
			tps = bonu[i].getDuree();  // on initialise la duree du bonus.
			bonu[i].estPris = true;	   // on indique qu'il n'est plus disponible pour le personnage.
			bonu[i].disponible = true; // on indique qu'il est disponible pour la génération de l'écran suivant.
			perso.aPrisB = true;	   // on indique que le personnage a pris un bonus.
		}
	}
	for (int i = 0; i < NB_BONUS; i++) // pour tous les bonus.
	{
		if (bonu[i].estPris) // si le bonus est pris..
		{
			if (i == 4) // si c'est le trou noir..
			{
				perso.enVie = false; //.. on meurt.
			}
		}
		if (tps > 0) // si le tps à été initialisé..
		{
			perso.setPos(perso.getPos().x - perso.getVit().x, perso.getPos().y); // on met à jour la position verticale du personnage (plus la vitesse du bonus est grande, plus il monte vite.).
			tps -= dt;															 // on décrémente la durée de dt à chaque itération de l'update.
		}
		else
		{
			if (i == 2) // pour le ressort, comme il ne disparait pas après utilisation.
				bonu[i].estPris = false;
			perso.aPrisB = false;
		}
	}

	if (px >= camX + 40) // si le personnage dépasse la caméra + 40, i.e si il passe sous la vue du joueur..
	{
		perso.enVie = false; // il meurt.
	}
	actionsAutomatiques(dt); // executions des action automatiques.
	updateEcran(dt);		 // mise à jour des écran.
}

void Jeu::testRegression()
{
	cout << "test de regression de la classe Jeu : " << endl;
	Jeu jeu;
	jeu.perso.setPos(50, 10);
	Plateforme p0(50, 10, 0, 0, 0.7, 2, -1);
	jeu.p.push_back(p0);
	jeu.update(1 / 60);
	assert(jeu.PcollPl == true);
	assert(jeu.Psaute == true);
	assert(jeu.Ptombe == false);
	assert(jeu.tpsSaut == 35);
	cout << "collision personnage/plateforme fonctionnelle." << endl;
	jeu.monstr[0].setPos(50, 10);
	jeu.monstr[0].setTailleM(1, 1);
	jeu.monstr[0].enVie = true;
	jeu.monstr[0].setResistance(1);
	jeu.perso.setPos(50, 10);
	jeu.update(1 / 60);
	assert(jeu.perso.enVie == false);
	assert(jeu.Ptombe == false);
	assert(jeu.Psaute == true);
	cout << "collision personnage/monstre fonctionnelle." << endl;
	projectile p1(50, 10, 0, 0);
	jeu.perso.placeProjTest(p1);
	jeu.update(1 / 60);
	assert(jeu.monstr[0].enVie == false);
	assert(jeu.Mtouche1 == true);
	cout << "collision projectile/monstre fonctionnelle" << endl;
	jeu.bonu[0].disponible = false;
	jeu.bonu[0].estPris = false;
	jeu.bonu[0].setPosBonus(50, 10);
	jeu.bonu[0].setTailleB(1, 1);
	jeu.bonu[0].setDuree(5);
	jeu.perso.enVie = true;
	jeu.perso.setPos(50, 10);
	jeu.update(1 / 60);
	assert(jeu.perso.aPrisB == true);
	assert(jeu.tps == jeu.bonu[0].getDuree());
	cout << "collision bonus/personnage fonctionnel" << endl;
}
