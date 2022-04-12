#ifndef __PLATEFORME_H__
#define ___PLATEFORME_H__
#include "vec2.h"

using namespace std;

class Plateforme
{
private:
    Vec2 pos;
    Vec2 dir;
    Vec2 taille;
    float vitesse;
    int res;

public:
    Plateforme();
    Plateforme(float posx, float posy, float dirx, float diry, float tx, float ty, int resist); /*! \brief tout est défini à partir des paramètres */
    ~Plateforme();
    Vec2 getPos() const;           /*! \brief renvoie la position de la plateforme*/
    void setPos(float x, float y); /*! \brief modifie la position d'une plateforme à partir d'un vec2 \param p en paramètre*/
    Vec2 getDir() const;           /*! \brief renvoie la direction de la plateforme*/
    void setDir(float x, float y);
    Vec2 getTaille() const;           /*! \brief renvoie la taille d'une plateforme*/
    void setTaille(float x, float y); /*! \brief modifie la taille de la plateforme à partir d'un float \param n en paramètre*/
    float getVitM() const;            /*! \brief renvoie la vitesse de la plateforme */
    void setVitM(float v);            /*! \brief met à jour la vitesse de la plateforme selon un parametre \param v*/
    int getRes() const;               /*! \brief renvoie la resistance d'une plateforme*/
    void setRes(int n);               /*! \brief modifie la resistance de la plateforme à partir d'un float \param n en paramètre*/
    void Update(double dt);           /*! \brief gère tous les déplacements*/
    bool estAfficheable();            /*! \brief renvoie vrai si la plateforme à une resistance à -1 ou supérieur à 0, faux sinon*/
    void descRes();                   /*! \brief décremente la resistance de 1*/
    void bougeAutoLateral(double dt); /*! \brief permet aux plateformes de se déplacer toutes seules*/
    void testRegression();            /*! \brief test de régression de la classe plateforme*/
};

#endif