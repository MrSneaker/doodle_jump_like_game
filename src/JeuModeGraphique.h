#ifndef __JEUMODEGRAPHIQUE_H__
#define __JEUMODEGRAPHIQUE_H__

using namespace std;

#include "vec2.h"
#include "Jeu.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>


//! \brief Pour gérer une image avec SDL2
class Image {

private:

    SDL_Surface *m_surface;
    SDL_Texture *m_texture;
    bool m_hasChanged;

public:
    Image () ;
    ~Image();
    void loadFromFile (const char* filename, SDL_Renderer * renderer);
    void loadFromCurrentSurface (SDL_Renderer * renderer);
    void draw (SDL_Renderer * renderer, int x, int y, int w=-1, int h=-1);
    SDL_Texture * getTexture() const;
    void setSurface(SDL_Surface * surf);
};



class JeuModeGRAPHIQUE
{
private:
    Jeu jeu;
    SDL_Window * window; /*fenetre SDL */ 
    int winx, winy;
    int TAILLE_BORDURE;
    SDL_Renderer * renderer; /*render SDL */
    SDL_Surface * m_surface ;
    SDL_Surface * background  = NULL ;
    SDL_Rect *rectangle;
    TTF_Font * font;
    Image font_im;
    SDL_Color font_color;
    Image im_projectile;
    Image im_perso;
    Image im_bonus;
    Image im_monstres;
    bool souris;
    bool touche;
    Mix_Chunk * sound; 
    bool withSound;

    
    
public:
    JeuModeGRAPHIQUE();
    ~JeuModeGRAPHIQUE();
    //void updatePlateau(Jeu &jeu); /*! \brief */
    void affichageInitGRAPHIQUE(); /*! \brief affichage de SDL2*/
    void affichageGRAPHIQUE(); /*! \brief affiche l'image dans la fenetre SDL2*/
    void boucleaffichageGRAPHIQUE(); /*! \brief rafraichissement de l'image*/
    void affDetruireGRAPHIQUE(); /*! \brief Détruit l'affichage*/

    
};




#endif