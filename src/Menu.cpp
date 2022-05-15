#include "Menu.h"

Menu::Menu() // on met toutes les textures à NULL.
{
  background = NULL;
  bouton[0] = NULL;
  bouton[1] = NULL;
  bouton[2] = NULL;
  titre = NULL;
  boutonJouer.x = DIMX / 2 - 100; // on définie la taille des boutons et du titre ici.
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

  titreRect.x = DIMX / 2 - 100;
  titreRect.y = 30;
  titreRect.h = 150;
  titreRect.w = 200;
}

Menu::~Menu()
{
}

void Menu::affichageInitMenu() // on initialise la SDL.
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

void Menu::initFont() // initialisation de la police.
{
  font = TTF_OpenFont("data/PIXEAB__.TTF", 15);
  font_color = {0, 0, 0};
}

void Menu::initTexture() // initialisation des textures.
{
  background = IMG_LoadTexture(renderer, "data/background.png");
  bouton[0] = IMG_LoadTexture(renderer, "data/bouton.png");
  bouton[1] = IMG_LoadTexture(renderer, "data/boutonQuitter.png");
  bouton[2] = IMG_LoadTexture(renderer, "data/boutonJouerTXT.png");
  titreSurf = TTF_RenderText_Solid(font, "FOODLE JUMP", font_color); // utilisation d'une surface pour créer la texture du titre.
  titre = SDL_CreateTextureFromSurface(renderer, titreSurf);
  SDL_FreeSurface(titreSurf); // on supprime la surface, car elle ne servira plus.
}

void Menu::initSon() // initialisation du son.
{
  musique = Mix_LoadMUS("data/Menu.mp3");
  if (!musique)
  {
    cout << "erreur lors du chargement de la musique" << endl;
    exit(1);
  }
}

void Menu::afficherMenu() // affichage du menu.
{
  SDL_RenderCopy(renderer, background, NULL, NULL);        // on affiche l'arrière plan.
  SDL_RenderCopy(renderer, bouton[0], NULL, &boutonJouer); // on fait ici le rendu des boutons puis du titre.
  SDL_RenderCopy(renderer, bouton[1], NULL, &boutonQuitter);
  SDL_RenderCopy(renderer, bouton[2], NULL, &boutonJouer2);
  SDL_RenderCopy(renderer, titre, NULL, &titreRect);
  int m = 0;                       // entier m servant à stocker le retour de Mix_PlayMusic.
  if (Mix_PlayingMusic() == 0)     // si la musique ne joue pas..
    m = Mix_PlayMusic(musique, 1); // alors on la joue.
  if (m == -1)                     // si PlayMusic rencontre une erreur.
    cout << "erreur à la lecture" << endl;
  SDL_RenderPresent(renderer); // on fait le rendu.
}

void Menu::afficheDetruireMenu() // destruction de toute les instances SDL (sans SDL_Quit).
{
  if (withSound)
    Mix_Quit();
  Mix_FreeMusic(musique);
  Mix_CloseAudio();
  TTF_CloseFont(font);
  TTF_Quit();
  SDL_DestroyTexture(background);
  SDL_DestroyTexture(bouton[0]);
  SDL_DestroyTexture(bouton[1]);
  SDL_DestroyTexture(bouton[2]);
  SDL_DestroyTexture(titre);
  IMG_Quit();
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
}

void Menu::jouerSDL(double dt)
{
  time_t t; // on randomise à chaque appel, pour changer la graine de génération du jeu.
  srand((unsigned)time(&t));
  Jeu jeu; // c'est pour cette raison que l'on ne passe pas en paramètre jeu et sl, car c'est eux qui sont affecté par l'aléatoire.
  JeuModeGRAPHIQUE sl;
  sl.InitCam();                   // on initialise la caméra.
  sl.boucleAffGRAPHIQUE(jeu, dt); // on rentre dans la boucle d'affichage.
}

void Menu::jouerTXT(double dt)
{
  time_t t; // très exactement le même principe que la procédure jouerSDL.
  srand((unsigned)time(&t));
  Jeu jeu;
  JeuModeTXT txt;
  txt.InitCam();
  txt.boucleAffTXT(jeu, dt);
}

void Menu::boucleMenu(double dt)
{
  affichageInitMenu(); // on initialise la SDL.
  initFont();          // on initialise tout le reste.
  initTexture();
  initSon();
  bool quit = false; // condition du while.
  int x, y;          // position de la souris.
  x = 0;
  y = 0;
  afficherMenu(); // on affiche le Menu.
  while (!quit)
  {
    while (SDL_PollEvent(&events)) // boucle d'évènements SDL.
    {
      switch (events.type)
      {
      case SDL_QUIT: // si on ferme la fenêtre..
        quit = true; // .. on ferme la fenêtre.
        break;
      case SDL_MOUSEBUTTONDOWN:                      // si on appuie sur un bouton de la souris..
        if (events.button.button == SDL_BUTTON_LEFT) // .. et que c'est le clique gauche..
        {
          x = events.motion.x; // .. on récupère la position de la souris.
          y = events.motion.y;
        }
        break;
      default:
        break;
      }
    }
    // Ici on tests si le clique de la souris était dans un bouton ou non.
    if ((x > boutonJouer.x) && (x < boutonJouer.x + boutonJouer.w) && (y > boutonJouer.y) && (y < boutonJouer.y + boutonJouer.h))
    {
      afficheDetruireMenu(); // on efface le menu.
      jouerSDL(dt);          // on lance le jeu.
      x = 0;                 // on reset la position de la souris.
      y = 0;
      affichageInitMenu(); // on réinitialise le menu.
      initFont();
      initTexture();
      initSon();
    }
    else if ((x > boutonJouer2.x) && (x < boutonJouer2.x + boutonJouer2.w) && (y > boutonJouer2.y) && (y < boutonJouer2.y + boutonJouer2.h))
    { // même principe mais avec jouerTXT.
      afficheDetruireMenu();
      jouerTXT(dt);
      x = 0;
      y = 0;
      affichageInitMenu();
      initFont();
      initTexture();
      initSon();
    }
    else if ((x > boutonQuitter.x) && (x < boutonQuitter.x + boutonQuitter.w) && (y > boutonQuitter.y) && (y < boutonQuitter.y + boutonQuitter.h))
    { // on quitte le menu.
      quit = true;
    }
    afficherMenu(); // si aucune des conditions n'est rempli, on continue d'afficher le menu.
  }
  afficheDetruireMenu(); // si on sort de la boucle, on détruit le menu.
  SDL_Quit();            // on quitte la SDL.
}
