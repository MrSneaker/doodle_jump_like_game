#include "Menu.h"

Menu::Menu(SDL_Renderer *rendu_) : {
    rendu = rendu_;
    texture = x = y = 0;
    select = nullptr;
    rCursor.x = 0; rCursor.y = 0; rCursor.w = 36; rCursor.h = 48;
    T_Menu = new SDL_Texture*[2];
    T_Menu[0] = Load("data/fond.png");
    T_Menu[1] = Load("data/commencer.png");
    
}


int Menu::Boucle(){
    int ret = -1;
    SDL_RenderPresent(rendu);
    SDL_Event events;
    bool quitter = false;
    t0 = t1 = 0;
    // tant que ce n'est pas la fin ...
    while (!quitter) {
        // tant qu'il y a des evenements à traiter (cette boucle n'est pas bloquante)
        while (SDL_PollEvent(&events)) {
            if (events.type == SDL_QUIT) quitter = true;
            if (events.type == SDL_KEYDOWN) {
                switch (events.key.keysym.sym) {
                    case SDLK_ESCAPE: quitter = true; break;
                    case SDLK_SPACE: ret = -1; quitter = true; break;
                }
            }
            if (events.type == SDL_MOUSEMOTION) {
                SDL_GetMouseState(&x,&y);
                if(//condition) select = &commencer;
                else select = nullptr;

            }
            if (events.type == SDL_MOUSEBUTTONDOWN) {
                if (events.button.button == SDL_BUTTON_LEFT) {
                    if(/*bouton commencer est pressé*/) {quitter = true; ret = 1; break;}
                }
            }
        }
        t1 = SDL_GetTicks();
        affichage();
        SDL_RenderPresent(rendu);
        SDL_Delay(20);
    }
    return ret;
}

void Menu::affichage(){
    
}

SDL_Texture* Menu::Load(const char* chemin){
    SDL_Surface *surface = IMG_Load(chemin);
    if (surface == NULL) {
        cout<<"Error: ne peut pas charger l'image "<< chemin <<endl;
        exit(1);
    }
    SDL_Surface * surfaceCorrectPixelFormat = SDL_ConvertSurfaceFormat(surface,SDL_PIXELFORMAT_ARGB8888,0);
    SDL_FreeSurface(surface);
    surface = surfaceCorrectPixelFormat;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(rendu,surface);
    if (texture == NULL) {
        cout << "Error: problème pour créer la texture "<< chemin<< endl;
        exit(1);
    }
    cout<<"texture de "<<chemin<<" chargé"<<endl;
    SDL_FreeSurface(surfaceCorrectPixelFormat);
    return texture;
}
