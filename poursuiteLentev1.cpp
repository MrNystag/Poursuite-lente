
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

// Permet de pouvoir sortir du programme en appuyant sur la croix
class SystemManager {
    public:
        // Here we will just have a couple public members for example purposes.
        bool running;
        SDL_Event events;
        void inputManager(); // Handle input.
        void renderingManager(); // Handle drawing pretty pictures.
};

void SystemManager::inputManager() {
    while(SDL_PollEvent(&events)) {
        if(events.type == SDL_QUIT)
            running = false;
    }
}

void SystemManager::renderingManager() {
    // Draw pretty pictures...
}

int main( int argc, char *argv[ ] )
{
    SDL_Surface *screen;
    SystemManager sysMgr;
    sysMgr.running = true;
    int lastrender = 0;
    if( SDL_Init( SDL_INIT_JOYSTICK | SDL_INIT_VIDEO ) == -1 )
    {
        printf( "Can't init SDL:  %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    atexit( SDL_Quit );
    screen = SDL_SetVideoMode( 640, 480, 16, SDL_HWSURFACE ); // initialisation de l'ecran 

    if( !screen)
    {
        printf( "Can't set video mode: %s\n", SDL_GetError( ) );
        return EXIT_FAILURE;
    }

    SDL_Rect position; // creation du point (rectangle)
    SDL_Surface *rectangle = NULL;
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 12, 12, 16, 1, 0, 0, 0); // taille et couleur

    position.x = screen->w/2; //structure pour placer le point au centre
    position.y = screen->h/2;
    SDL_Event event;
    while(sysMgr.running) // boucle qui travaille tant qu'on appuye pas sur la croix pour quitter
    {
    sysMgr.inputManager();
        sysMgr.renderingManager();
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
    SDL_BlitSurface(rectangle, NULL, screen, &position); // Collage de la surface sur l'écran
    SDL_Flip(screen); // Mise à jour de l'écran
   // SDL_Delay( 100 );
    SDL_FillRect(rectangle, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_BlitSurface(rectangle, NULL, screen, &position); // Collage de la surface sur l'écran
    position.x = (position.x +10)%screen->w;
    SDL_Delay( 2000 );


            }



  return EXIT_SUCCESS;

}


