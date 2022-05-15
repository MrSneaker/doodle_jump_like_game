#ifndef __BONUS_H__
#define __BONUS_H__
#include "vec2.h"

#include <string>

using namespace std;

class bonus
{
private:
    Vec2 position;
    string nomBonus;
    float vitesse;
    float duree;
    Vec2 taille;

public:
    /*! \brief booléen indiquant si le bonus est pris ou non.*/
    bool estPris;
    /*! \brief booléen indiquant si le bonus est disponible à la génération ou non.*/
    bool disponible;
    /*! \brief Constructeur de la classe.*/
    bonus();
    /*! \brief Destructeur de la classe*/
    ~bonus();
    /*! \brief renvoie la taille du bonus */
    Vec2 getTailleB() const;
    /*! \brief met à jour la taille avec les paramètres \param x, \param y*/
    void setTailleB(float x, float y);
    /*! \brief renvoie la vitesse du bonus */
    float getVitB() const;
    /*! \brief met à jour la vitesse du bonus selon un parametre \param v*/
    void setVitB(float v);
    /*! \brief renvoie la position du bonus en x et y*/
    Vec2 getPosBonus() const;
    /*! \brief met à jour la position du bonus selon une position en paramètre \param p*/
    void setPosBonus(float x, float y);
    /*! \brief renvoie le nom du bonus (permet de définir plusieurs apparences)*/
    string getNomB() const;
    /*! \brief met à jour le nom du bonus selon un string \param nom en paramètre*/
    void setNomB(const string nomBonus);
    /*! \brief renvoie la duree du bonus */
    float getDuree() const;
    /*! \brief met à jour la duree du bonus selon un parametre \param d*/
    void setDuree(float d);
    /*! \brief test de regression de la classe bonus*/
    void testRegression();
};

#endif