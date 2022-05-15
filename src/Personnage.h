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
    Vec2 position;           /*!   structure contenant la position en coordonnées x,y*/
    vector<projectile> proj; /*!   vector de vector de projectile du personnage */
    Vec2 direction;          /*!   le vecteur de direction du personnage*/
    Vec2 vitesse;            /*!   la vitesse du personnage*/
    string nom;              /*!   le nom du personnage*/
    Vec2 taille;             /*!   la taille du personnage*/
    float force;

public:
    /*! \brief booléen indiquant si le personnage est en vie ou non*/
    bool enVie;
    /*! \brief booléen indiquant si le personnage a pris un bonus ou non*/
    bool aPrisB;
     /*! \brief position de base : 0,0; projectile à NULL; direction, vitesse à 0, nom à "p0", enVie à true*/
    Personnage();     
    /*! \brief supprimes les projectiles, tout à 0(pos x,y; direction; vitesse), nom à NULL, enVie à NULL*/               
    ~Personnage();    
     /*! \brief renvoie la position en x et en y du personnage*/                
    Vec2 getPos() const;   
     /*! \brief met à jour la position du personnage selon une position en paramètre \param p*/          
    void setPos(float x, float y);  
     /*! \brief renvoie la direction du personnage */ 
    Vec2 getDir() const;        
     /*! \brief renvoie le nombre de projectile */     
    int getNombreProj() const; 
    /*! \brief renvoie le vecteur projectile demandé si il existe*/     
    projectile &getProjectile(int n); 
    /*! \brief renvoie le vecteur projectile demandé si il existe pour l'affichage.*/
    projectile getProjectileAff(int n) const;
    /*! \brief renvoie le vecteur de taille du personnage.*/
    Vec2 getTaille() const;
    /*! \brief met à jour la taille du personnage en fonction des réels \param x, \param y.*/
    void setTaille(float x, float y);
    /*! \brief renvoie la vitesse du personnage */
    Vec2 getVit() const;       
    /*! \brief met à jour la vitesse du personnage selon un paramètre vitesse \param v*/      
    void setVit(float vx, float vy); 
    /*! \brief déplace le personnage à droite et modifie sa position.*/
    void deplacerD(double dt);    
     /*! \brief déplace le personnage à gauche et modifie sa position.*/   
    void deplacerG(double dt);    
    /*! \brief fait sauter le personnage, le déplace vers le haut en modifiant sa position.*/  
    void saut(double dt);     
    /*! \brief fait tomber le personnage, le déplace vers le haut en modifiant sa position.*/       
    void tombe(double dt);   
    /*! \brief renvoie le nom du personnage (permet de définir plusieurs apparences)*/        
    const string &getNom() const;    
    /*! \brief met à jour le nom du personnage selon un string \param nom en paramètre*/
    void setNom(const string nomP);  
    /*! \brief fait tirer le personnage en créant un veteur projectile*/
    void creerProj(double dt);  
    /*! \brief supprime un projectile*/     
    void detruitProj(int i);    
    /*! \brief test toutes les fonctions de la classe Personnage*/     
    void testRegression();   
    /*! \brief Procédure permettant le test des collisions du projectile dans la classe Jeu.*/
    void placeProjTest(projectile p);        
};

#endif
