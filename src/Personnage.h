#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <vector>
#include <string>
#include "projectile.h"
#include "vec2.h"
#include <unistd.h>

using namespace std;

class Personnage
{
private:
    Vec2 position;           /*! \brief structure contenant la position en coordonnées x,y*/
    vector<projectile> proj; /*! \brief vector de vector de projectile du personnage */
    Vec2 direction;          /*! \brief le vecteur de direction du personnage*/
    Vec2 vitesse;            /*! \brief la vitesse du personnage*/
    string nom;              /*! \brief le nom du personnage*/
    Vec2 taille;             /*! \brief la taille du personnage*/
    float force;

public:
    bool enVie;                       /*! \brief info si le personnage est en vie ou non*/
    bool aPrisB;
    Personnage();                     /*! \brief position de base : 0,0; projectile à NULL; direction, vitesse à 0, nom à "p0", enVie à true*/
    ~Personnage();                    /*! \brief supprimes les projectiles, tout à 0(pos x,y; direction; vitesse), nom à NULL, enVie à NULL*/
    Vec2 getPos() const;              /*! \brief renvoie la position en x et en y du personnage*/
    void setPos(float x, float y);    /*! \brief met à jour la position du personnage selon une position en paramètre \param p*/
    Vec2 getDir() const;              /*! \brief renvoie la direction du personnage */
    int getNombreProj() const;        /*! \brief renvoie le nombre de projectile */
    projectile &getProjectile(int n); /*! \brief renvoie le vecteur projectile demandé si il existe*/
    projectile getProjectileAff(int n) const;
    const projectile &getProjectileAffSdl(int n) const;
    Vec2 getTaille() const;
    void setTaille(float x, float y);
    Vec2 getVit() const;             /*! \brief renvoie la vitesse du personnage */
    void setVit(float vx, float vy); /*! \brief met à jour la vitesse du personnage selon un paramètre vitesse \param v*/
    void deplacerD(double dt);       /*! \brief déplace le personnage à droite et modifie sa position x de +1*/
    void deplacerG(double dt);       /*! \brief déplace le personnage à gauche et modifie sa position x de -1*/
    void saut(double dt);            /*! \brief fait sauter le personnage, le déplace vers le haut en modifiant sa position y de +1*/
    void tombe(double dt);           /*! \brief fait tomber le personnage, le déplace vers le haut en modifiant sa position y de -1*/
    const string &getNom() const;    /*! \brief renvoie le nom du personnage (permet de définir plusieurs apparences)*/
    void setNom(const string nomP);  /*! \brief met à jour le nom du personnage selon un string \param nom en paramètre*/
    void creerProj(double dt);       /*! \brief fait tirer le personnage en créant un veteur projectile*/
    void detruitProj(int i);         /*! \brief supprime un projectile*/
    void testRegression();           /*! \brief test toutes les fonctions de la classe Personnage*/
};

#endif
