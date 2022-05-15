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
    /*! \brief variable permettant d'obtenir la position verticale de base lors de la construction, pour bougeAuto. */
    float posXbase;
    /*! \brief constructeur sans paramètre.*/
    Plateforme();
    /*! \brief constructeur, tout est défini à partir des paramètres */
    Plateforme(float posx, float posy, float dirx, float diry, float tx, float ty, int resist);
    /*! \brief destructeur. */
    ~Plateforme();
    /*! \brief renvoie la position de la plateforme*/
    const Vec2 &getPos() const;
    /*! \brief modifie la position d'une plateforme à partir d'un vec2 \param p en paramètre*/
    void setPos(float x, float y);
    /*! \brief renvoie la direction de la plateforme*/
    Vec2 getDir() const;
    /*! \brief Met à jour la direction de la plateforme selon deux réels passées en paramètre \param x, \param y.*/
    void setDir(float x, float y);
    /*! \brief renvoie la taille d'une plateforme*/
    Vec2 getTaille() const;
    /*! \brief modifie la taille de la plateforme à partir d'un float \param x et \param y en paramètre*/
    void setTaille(float x, float y);
    /*! \brief renvoie la vitesse de la plateforme */
    float getVitM() const;
    /*! \brief met à jour la vitesse de la plateforme selon un parametre \param v*/
    void setVitM(float v);
    /*! \brief renvoie la resistance d'une plateforme*/
    int getRes() const;
    /*! \brief modifie la resistance de la plateforme à partir d'un float \param n en paramètre*/
    void setRes(int n);
    /*! \brief gère tous les déplacements*/
    void Update(double dt);
    /*! \brief renvoie vrai si la plateforme à une resistance à -1 ou supérieur à 0, faux sinon*/
    bool estAfficheable() const;
    /*! \brief décremente la resistance de 1*/
    void descRes();
    /*! \brief permet aux plateformes de se déplacer toutes seules*/
    void bougeAuto(double dt);
    /*! \brief test de régression de la classe plateforme*/
    void testRegression();
};

#endif