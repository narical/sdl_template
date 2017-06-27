#include <SDL2/SDL.h>
#include <stdio.h>

enum ErrType { VID_INIT, WIN_CREATE, REND_CREATE };
void ErrorMsg ( ErrType );

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main (int argc, char **args)
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer *renderer = nullptr;

	if (SDL_Init( SDL_INIT_VIDEO ) < 0) ErrorMsg( VID_INIT );
	else
	{
		window = SDL_CreateWindow
			("Hello World",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
			
		if ( window == nullptr ) ErrorMsg( WIN_CREATE );
		
		else
		{
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if (renderer == nullptr) ErrorMsg( REND_CREATE );
			
			screenSurface = SDL_GetWindowSurface( window );
			SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0x00, 0xFF, 0x00 ) );
			SDL_UpdateWindowSurface( window );
			SDL_Delay( 3000 );
		}
	}

	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}



void ErrorMsg( ErrType error ) {
	switch ( error )
	{
		case VID_INIT:
			printf( "SDL initialization error: %s\n", SDL_GetError() );
			break;
			
		case WIN_CREATE:
			printf( "Window creation error: %s\n", SDL_GetError() );
			SDL_Quit();
			break;
			
		case REND_CREATE:
			printf( "Renderer creation error: %s\n", SDL_GetError() );
			SDL_Quit();
			break;
	}
	exit(-1);
}
