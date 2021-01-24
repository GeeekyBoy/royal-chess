#ifndef LIFECYCLE_H
#define LIFECYCLE_H

#include "definitions.h"

#define INCBIN_PREFIX RAW_
#include "lib/incbin/incbin.h"
INCBIN(splashDialog, __ASSETS__ "dialogs/splash.svg");

GameInstance Game = {
	SDL_FALSE,
	{
		SCREEN_W,
		SCREEN_H,
		SCREEN_NAME,
		NULL,
		NULL
	},
	game_init,
	game_quit
};

void newGame() {
	data.player = 1;
	data.playerState = NONE;
	data.kingPos[0] = (Coordinate){0, 4};
	data.kingPos[1] = (Coordinate){7, 4};
	data.undoData = NULL;
	data.undoDataSize = 0;
	data.nextUndoIndex= -1;
	data.capturedNum[0] = 0;
	data.capturedNum[1] = 0;
	data.enPassantData = (Coordinate){-1, -1};
	_Bool castlingData[2][3] = {{1, 1, 1}, {1, 1, 1}};
	char boardData[8][8] = {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
							{'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
							{'.', '.', '.', '.', '.', '.', '.', '.'},
							{'.', '.', '.', '.', '.', '.', '.', '.'},
							{'.', '.', '.', '.', '.', '.', '.', '.'},
							{'.', '.', '.', '.', '.', '.', '.', '.'},
							{'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
							{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};
	memmove(data.castlingData, castlingData, sizeof(_Bool[2][3]));
	memmove(data.boardData, boardData, sizeof(char[8][8]));
	resetUndoData();
}

void game_init(void) {
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO |
               SDL_INIT_EVENTS | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC |
               SDL_INIT_GAMECONTROLLER) != 0) {
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "SDL Error", SDL_GetError(),
                             NULL);
    exit(1);
  }

    unsigned int w = Game.screen.w;
	unsigned int h = Game.screen.h;
	const char* name = Game.screen.name;
 
	Game.screen.window = SDL_CreateWindow(
		name,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		w, h, 0
	);
	SDL_SetWindowFullscreen(Game.screen.window, isFullScreen);
	Game.screen.renderer = SDL_CreateRenderer(
		Game.screen.window, -1,
		SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
	);
	if(TTF_Init()==-1) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
						"SDL_TTF Error",
						TTF_GetError(),
						NULL);
    	exit(2);
	}
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) == -1) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
				"SDL_Mixer Error",
				Mix_GetError(),
				NULL);
    	exit(2);
	}
	splashDialog = svg2tex((char*)RAW_splashDialogData);
	SDL_ShowCursor(SDL_DISABLE);
	Game.running = SDL_TRUE;
}

void game_quit(void) {
	SDL_DestroyRenderer(Game.screen.renderer);
	SDL_DestroyWindow(Game.screen.window);
	Game.screen.window = NULL;
	Game.screen.renderer = NULL;
	resetTextures();
	resetFonts();
	resetAudio();
	TTF_Quit();
	SDL_Quit();
}

#endif