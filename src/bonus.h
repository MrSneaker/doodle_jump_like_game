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
    bool estPris;
    bonus(); /*! \brief */
    ~bonus();
    Vec2 getTailleB() const;             /*! \brief renvoie la taille du bonus */
    void setTailleB(float x, float y);   /*! \brief met à jour la taille avec les paramètres \param x, \param y*/
    float getVitB() const;               /*! \brief renvoie la vitesse du bonus */
    void setVitB(float v);               /*! \brief met à jour la vitesse du bonus selon un parametre \param v*/
    Vec2 getPosBonus() const;            /*! \brief renvoie la position du monstre en x et y*/
    void setPosBonus(float x, float y);  /*! \brief met à jour la position du monstre selon une position en paramètre \param p*/
    string getNomB() const;              /*! \brief renvoie le nom du bonus (permet de définir plusieurs apparences)*/
    void setNomB(const string nomBonus); /*! \brief met à jour le nom du bonus selon un string \param nom en paramètre*/
    float getDuree() const;              /*! \brief renvoie la duree du bonus */
    void setDuree(float d);              /*! \brief met à jour la duree du bonus selon un parametre \param d*/
    void testRegression();               /*! \brief test de regression de la classe bonus*/
};

#endif