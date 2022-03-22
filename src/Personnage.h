#ifndef __PERSONNAGE_H__
#define __PERSONNAGE_H__

#include <vector>
#include <string>

using namespace std;

struct pos 
{
    float x,y; 
};

class Personnage
{
    private:
        pos position; /*! \brief structure contenant la position en coordonnées x,y*/
        vector<float> * projectile; /*! \brief tableau dynamique de projectile */
        vector<float> direction; /*! \brief le vecteur de direction du personnage*/
        float vitesse;/*! \brief la vitesse du personnage*/
        string nom;/*! \brief le nom du personnage*/
        bool enVie;/*! \brief info si le personnage est en vie ou non*/
    public:
        Personnage();/*! \brief position de base : 0,0; projectile à NULL; direction, vitesse à 0, nom à "p0", enVie à true*/
        ~Personnage();/*! \brief delete des projectiles, tout à 0(pos x,y; direction; vitesse), nom à NULL, enVie à NULL*/
        pos getPos() const;/*! \brief renvoie la position en x et en y du personnage*/
        void setPos(pos p);/*! \brief met à jour la position du personnage selon une position en paramètre \param p*/
        vector<float> getDir() const; /*! \brief renvoie la direction du personnage */
        void setDir(vector<float> d); /*! \brief met à jour la direction selon un vecteur direction \param d en paramètre*/
        float getVit() const;/*! \brief renvoie la vitesse du personnage */
        void setVit(float v);/*! \brief met à jour la vitesse du personnage selon un paramètre vitesse \param v*/
        void deplacerD();/*! \brief déplace le personnage à droite */
        void deplacerG();/*! \brief déplace le personnage à gauche */
        const string& getNom() const;/*! \brief renvoie le nom du personnage (permet de définir plusieurs apparences)*/
        void setNom(const string nom);/*! \brief met à jour le nom du personnage selon un string \param nom en paramètre*/
        bool estEnVie();/*! \brief renvoie true si en vie, false sinon*/




};


#endif
