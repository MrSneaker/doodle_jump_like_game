#ifndef MENU_H
#define MENU_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include "JeuModeGraphique.h"
#include "JeuModeTXT.h"

using namespace std;

class Menu
{
private:
    SDL_Renderer *renderer;  /*!  Rendu SDL.*/
    SDL_Window *window;      /*!  Fenêtre SDL.*/
    TTF_Font *font;          /*!  Police d'écriture SDL.*/
    SDL_Color font_color;    /*!  Couleur de police SDL.*/
    SDL_Event events;        /*!  Structure d'évènement SDL.*/
    Mix_Music *musique;      /*!  Musique du menu.*/
    SDL_Texture *background; /*!  Texture de l'arrière plan.*/
    SDL_Texture *bouton[3];  /*!  tableau statique une dimension de taille 3 de texture des boutons de choix.*/
    SDL_Texture *titre;      /*!  Texture du titre.*/
    SDL_Rect boutonJouer;    /*!  Le rectangle d'application du bouton "JOUER SDL".*/
    SDL_Rect boutonJouer2;   /*!  Le rectangle d'application du bouton "JOUER TXT".*/
    SDL_Rect boutonQuitter;  /*!  Le rectangle d'application du bouton "QUITTER".*/
    SDL_Rect titreRect;      /*!  Le rectangle d'application du titre.*/
    SDL_Surface *titreSurf;  /*!  La surface servant à construire la texture du titre.*/
    bool withSound;          /*!  Booléen vérifiant le bon déroulement de l'initialisation de SDL_Mixer.*/
    const int DIMX = 300;    /*!  Dimension de l'écran en X.*/
    const int DIMY = 600;    /*!  Dimension de l'écran en Y.*/

public:
/*! \brief Constructeur du menu, initialise les textures à NULL.*/
    Menu();     
    /*! \brief Destructeur du menu.*/                
    ~Menu();         
    /*! \brief Initialisation de la SDL pour le menu.*/           
    void affichageInitMenu(); 
    /*! \brief Initialisation des polices d'écritures.*/  
    void initFont(); 
    /*! \brief Initialisation des textures.*/           
    void initTexture(); 
    /*! \brief Initialisation des sons.*/        
    void initSon();   
    /*! \brief affichage des éléments du menu sur le rendu.*/          
    void afficherMenu();    
    /*! \brief Procédure servant à démarrer une partie sur l'affichage SDL, à chaque appel la graine du jeu est regénérée, on prend en paramètre le double \param dt la vitesse de rafraichissement du jeu.*/    
    void jouerSDL(double dt);  
    /*! \brief Procédure servant à démarrer une partie sur l'affichage TXT, à chaque appel la graine du jeu est regénérée, on prend en paramètre le double \param dt la vitesse de rafraichissement du jeu.*/ 
    void jouerTXT(double dt); 
    /*! \brief Boucle d'affichage du menu, détectant les événements, on prend en paramètre le double \param dt la vitesse de rafraichissement du jeu.*/  
    void boucleMenu(double dt); 
    /*! \brief Procédure de destruction du menu pour détruire la fenêtre, appelée à chaque partie lancée.*/
    void afficheDetruireMenu(); 
};

#endif