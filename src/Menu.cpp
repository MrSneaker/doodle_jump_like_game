#include "Menu.h"

Menu::Menu()
{
  background = NULL;
  bouton[0] = NULL;
  bouton[1] = NULL;
  bouton[2] = NULL;
}

Menu::~Menu()
{
}

void Menu::affichageInitMenu()
{

  // Initialisation de la SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
    SDL_Quit();
    exit(1);
  }
  // Initialisation de l'écriture
  if (TTF_Init() != 0)
  {
    cout << "Erreur lors de l'initialisation de la SDL_ttf : " << TTF_GetError() << endl;
    SDL_Quit();
    exit(1);
  }

  // Creation de la fenetre
  window = SDL_CreateWindow("Foodle_Jump", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DIMX, DIMY, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (window == NULL)
  {
    cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
    SDL_Quit();
    exit(1);
  }

  int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP;
  if (!(IMG_Init(imgFlags) & imgFlags))
  {
    cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << endl;
    SDL_Quit();
    exit(1);
  }

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
  {
    cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
    cout << "No sound !!!" << endl;
    // SDL_Quit();exit(1);
    withSound = false;
  }
  else
    withSound = true;

  // Initialisation du rendu
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
  {
    cout << "erreur lors de la création du rendu " << endl;
    SDL_Quit();
    exit(1);
  }
}

void Menu::initFont()
{
  font = TTF_OpenFont("data/PIXEAB__.TTF", 15);
  font_color = {0, 0, 0};
}

void Menu::initTexture()
{
  background = IMG_LoadTexture(renderer, "data/background.png");
  bouton[0] = IMG_LoadTexture(renderer, "data/bouton.png");
  bouton[1] = IMG_LoadTexture(renderer, "data/boutonQuitter.png");
  bouton[2] = IMG_LoadTexture(renderer, "data/boutonJouerTXT.png");
}

void Menu::initSon()
{
}

void Menu::afficherMenu()
{
  SDL_RenderCopy(renderer, background, NULL, NULL);
  titreSurf = TTF_RenderText_Solid(font, "FOODLE JUMP", font_color);
  titre = SDL_CreateTextureFromSurface(renderer, titreSurf);
  SDL_FreeSurface(titreSurf);
  SDL_Rect titreRect;
  titreRect.x = DIMX / 2 - 100;
  titreRect.y = 30;
  titreRect.h = 150;
  titreRect.w = 200;

  boutonJouer.x = DIMX / 2 - 100;
  boutonJouer.y = DIMY / 2 - 100;
  boutonJouer.w = 200;
  boutonJouer.h = 100;

  boutonJouer2.x = DIMX / 2 - 100;
  boutonJouer2.y = DIMY / 2;
  boutonJouer2.w = 200;
  boutonJouer2.h = 100;

  boutonQuitter.x = DIMX / 2 - 100;
  boutonQuitter.y = DIMY / 2 + 100;
  boutonQuitter.w = 200;
  boutonQuitter.h = 100;

  SDL_RenderCopy(renderer, bouton[0], NULL, &boutonJouer);
  SDL_RenderCopy(renderer, bouton[1], NULL, &boutonQuitter);
  SDL_RenderCopy(renderer, bouton[2], NULL, &boutonJouer2);
  SDL_RenderCopy(renderer, titre, NULL, &titreRect);
  SDL_RenderPresent(renderer);
}

void Menu::afficheDetruireMenu()
{
  if (withSound)
    Mix_Quit();
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(bouton[0]);
  SDL_DestroyTexture(bouton[1]);
  SDL_DestroyTexture(bouton[2]);
  SDL_DestroyTexture(titre);
  IMG_Quit();
  SDL_DestroyRenderer(renderer);
}

void Menu::jouerSDL(Jeu jeu, JeuModeGRAPHIQUE sl, double dt)
{
  time_t t;
  srand((unsigned)time(&t));
  sl.InitCam();
  sl.boucleAffGRAPHIQUE(jeu, dt);
}

void Menu::jouerTXT(Jeu jeu, JeuModeTXT txt, double dt)
{
  time_t t;
  srand((unsigned)time(&t));
  txt.InitCam();
  txt.boucleAffTXT(jeu, dt);
}

void Menu::boucleMenu(double dt)
{
  affichageInitMenu();
  initFont();
  initTexture();
  initSon();
  Jeu jeu;
  JeuModeGRAPHIQUE sl;
  JeuModeTXT txt;
  SDL_Event events;
  bool quit = false;
  int x, y;
  x = 0;
  y = 0;
  afficherMenu();
  while (!quit)
  {
    while (SDL_PollEvent(&events))
    {
      switch (events.type)
      {
      case SDL_QUIT:
        quit = true;
        break;
      case SDL_MOUSEBUTTONDOWN:
        x = events.motion.x;
        y = events.motion.y;
        break;
      default:
        break;
      }
    }
    boutonJouer.x = DIMX / 2 - 100;
    boutonJouer.y = DIMY / 2 - 100;
    boutonJouer.w = 200;
    boutonJouer.h = 100;

    boutonJouer2.x = DIMX / 2 - 100;
    boutonJouer2.y = DIMY / 2;
    boutonJouer2.w = 200;
    boutonJouer2.h = 100;

    boutonQuitter.x = DIMX / 2 - 100;
    boutonQuitter.y = DIMY / 2 + 100;
    boutonQuitter.w = 200;
    boutonQuitter.h = 100;
    if ((x > boutonJouer.x) && (x < boutonJouer.x + boutonJouer.w) && (y > boutonJouer.y) && (y < boutonJouer.y + boutonJouer.h))
    {
      afficheDetruireMenu();
      jouerSDL(jeu, sl, dt);
      x = 0;
      y = 0;
      affichageInitMenu();
      initFont();
      initTexture();
      initSon();
    }
    else if ((x > boutonJouer2.x) && (x < boutonJouer2.x + boutonJouer2.w) && (y > boutonJouer2.y) && (y < boutonJouer2.y + boutonJouer2.h))
    {
      afficheDetruireMenu();
      jouerTXT(jeu, txt, dt);
      x = 0;
      y = 0;
      affichageInitMenu();
      initFont();
      initTexture();
      initSon();
    }
    else if ((x > boutonQuitter.x) && (x < boutonQuitter.x + boutonQuitter.w) && (y > boutonQuitter.y) && (y < boutonQuitter.y + boutonQuitter.h))
    {
      quit = true;
    }
    afficherMenu();
  }
  SDL_Quit();
}
