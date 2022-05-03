#include "Menu.h"

Menu::Menu(SDL_Renderer *rendu_) : commencer(1,700,600,70,500),
    charger(2,700,750,70,500), option(3,700,900,70,500) {
    rendu = rendu_;
    texture = x = y = 0;
    select = nullptr;
    rCursor.x = 0; rCursor.y = 0; rCursor.w = 36; rCursor.h = 48;
    T_Menu = new SDL_Texture*[2];
    T_Menu[0] = Load("data/img/fond.png");
    T_Menu[1] = Load("data/img/b_commencer.png");
    
}
