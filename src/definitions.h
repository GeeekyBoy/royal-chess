#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <ctype.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define SDL_MAIN_HANDLED
#define NANOSVG_IMPLEMENTATION
#define NANOSVG_ALL_COLOR_KEYWORDS
#define NANOSVGRAST_IMPLEMENTATION

#include "lib/nanosvg/nanosvg.h"
#include "lib/nanosvg/nanosvgrast.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_W 640
#define SCREEN_H 480
#define SCREEN_NAME "Royal Chess"
#define SAVE_BTN_X 32
#define SAVE_BTN_Y 24
#define END_BTN_X 268
#define END_BTN_Y 24
#define UNDO_BTN_X 32
#define UNDO_BTN_Y 66
#define SCREEN_MODE_BTN_X 268
#define SCREEN_MODE_BTN_Y 66
#define IN_GAME_BTN_W 80
#define IN_GAME_BTN_H 30
#define DIALOG_BTN_W 160
#define DIALOG_BTN_H 60
#define RESIGN_CONFIRM_BTN_X 135
#define RESIGN_CONFIRM_BTN_Y 253
#define DRAW_OFFER_BTN_X 345
#define DRAW_OFFER_BTN_Y 253
#define EXIT_CONFIRM_BTN_X 135
#define EXIT_CONFIRM_BTN_Y 328
#define END_CANCEL_BTN_X 345
#define END_CANCEL_BTN_Y 328
#define SAVE_CONFIRM_BTN_X 135
#define SAVE_CONFIRM_BTN_Y 278
#define SAVE_CANCEL_BTN_X 345
#define SAVE_CANCEL_BTN_Y 278
#define DRAW_CONFIRM_BTN_X 135
#define DRAW_CONFIRM_BTN_Y 278
#define DRAW_CANCEL_BTN_X 345
#define DRAW_CANCEL_BTN_Y 278
#define SAVE_OK_BTN_X 240
#define SAVE_OK_BTN_Y 278
#define BISHOP_PROMOTION_BTN_X 155
#define KNIGHT_PROMOTION_BTN_X 245
#define QUEEN_PROMOTION_BTN_X 335
#define ROOK_PROMOTION_BTN_X 425
#define PROMOTION_BTN_Y 278
#define PROMOTION_BTN_WH 60
#define MAIN_MENU_BTN_X 240
#define NEW_GAME_BTN_Y 230
#define LOAD_GAME_BTN_Y 305
#define EXIT_GAME_BTN_Y 380
#define DUMP_PIECE '.'

int screenScale = 1;

const SDL_Color brownTxtColor = {110, 39, 4};
const SDL_Color goldenTxtColor = {185, 131, 22};
typedef enum {
  MAIN_MENU,
  PLAYER_ONE_VICTORY_WINDOW,
  PLAYER_TWO_VICTORY_WINDOW,
  IN_GAME_WINDOW,
  PROMOTION_WINDOW,
  DRAW_AGREEMENT,
  DRAW_WINDOW,
  SAVE_WINDOW,
  SAVE_COMPLETE_WINDOW,
  END_GAME_WINDOW
} GameWindow;

typedef enum { NONE, CHECK, CHECKMATE, STALEMATE, DEAD_POSITION } PlayerState;

typedef struct {
  SDL_Texture *tex;
  int width;
  int height;
} Image;

typedef struct {
  int row;
  int col;
} Coordinate;

typedef struct {
  char firstPiece;
  Coordinate firstSquare;
  char secondPiece;
  Coordinate secondSquare;
  int capturedPlayer;
  char newRank;
  _Bool castlingData[2][3];
  Coordinate enPassantData;
  PlayerState playerState;
  char algebraicData[10];
} Step;

typedef struct {
  int player;
  PlayerState playerState;
  Coordinate kingPos[2];
  Step *undoData;
  int undoDataSize;
  int nextUndoIndex;
  char capturedPieces[2][15];
  int capturedNum[2];
  _Bool castlingData[2][3];
  Coordinate enPassantData;
  char boardData[8][8];
} Gamedata;

typedef struct {
  SDL_bool running;
  struct {
    unsigned int w;
    unsigned int h;
    const char *name;
    SDL_Window *window;
    SDL_Renderer *renderer;
  } screen;

  void (*init)(void);
  void (*quit)(void);
} GameInstance;

Gamedata data;

Coordinate promotedPieceSquare;

GameInstance Game;

Image board, playerOneCaptured, playerTwoCaptured, logTile, playerOneTile,
    playerTwoTile, drawDialog, mainMenuDialog, saveGameDialog,
    drawAgreementDialog, promotionDialog, splashDialog, saveConfirmedDialog, endGameDialog,
    playerOneVictoryDialog, playerTwoVictoryDialog, gameBackgroundTile,
    saveGameBtn, endGameBtn, fullscreenBtn, windowedBtn, undoBtn, selectedTile,
    allowedTile, lightTile, darkTile, kingTile, rookTile, queenTile, bishopTile,
    knightTile, pawnTile, kingDarkTile, rookDarkTile, queenDarkTile,
    bishopDarkTile, knightDarkTile, pawnDarkTile, kingSmallTile, rookSmallTile,
    queenSmallTile, bishopSmallTile, knightSmallTile, pawnSmallTile,
    kingDarkSmallTile, rookDarkSmallTile, queenDarkSmallTile,
    bishopDarkSmallTile, knightDarkSmallTile, pawnDarkSmallTile, logTxt,
    noCapturedTxt;

TTF_Font *robotoBold;
SDL_Cursor *arrowCursor, *handCursor;
Mix_Chunk *moveSound, *checkSound, *checkmateSound, *stalemateSound,
    *victorySound, *drawSound, *warningSound, *deadPositionSound,
    *promotionSound, *undoSound, *redoSound, *errorSound, *clickSound, *startGameSound;

Coordinate allowedSquares[32];
int allowedSquaresNum = 0;

Coordinate selectedSquare = {-1, -1};

int texInitState = 0;
int resFactor = 1;
int logHeight = 0;
int logScrollPos = 0;

_Bool shouldExit = 0;
_Bool isFullScreen = 1;

GameWindow currentWindow = MAIN_MENU;

void updateKingPos(char square, Coordinate newCoordinate);
void switchPlayer();
void switchPlayer();
void applyPlayerState();
void renderFrame();
void newGame();
void saveGame();
void resetSelection();
void loadGame();
void game_init(void);
void game_quit(void);
void resetCapturedPiecesInventory();
void resetUndoData();
void resetTextures();
void resetFonts();
void fireDumpEvent();
void resetAudio();
void savePGN();
void updateLogTxt();
void goToMainMenu();
void endGameByCheckmate();
void endGameByDraw();
void playWarningSound();
void resetLogTxt();
void getMissingFiles();
void playSound();
void handleMouseEvent(int x, int y, int btn, Uint32 type);
void appednAlgebraicNotation(_Bool isPromoted);
char* getAlgebraicLog();
void doPromotion (Coordinate firstSquare, Coordinate secondSquare, _Bool isRedo);
void handleMousewheelEvent(int x, int y, int steps);
_Bool isToBeChecked(Coordinate firstSquare, Coordinate secondSquare);
_Bool isMovable(Coordinate coordinate, _Bool isInternal);
void doCastling(Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo);
void doEnpassant (Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo);
void askForMove(Coordinate firstSquare, Coordinate secondSquare);
void setCastlingState (Coordinate coordinate);
void setEnPassantData (Coordinate firstSquare, Coordinate secondSquare);
void addUndoData(char firstPiece, Coordinate firstSquare, char secondPiece,
                 Coordinate secondSquare, int capturedPlayer);
void undo();
void redo();
char getRightPiece(char square, _Bool isOwned);
char *getPath(char *relPath);
Image svg2tex (char *filename);
Image mkTxt(char *txt, TTF_Font *font, SDL_Color color, int maxWidth);
Coordinate getDirection (int directionID);
Coordinate getActualCoordinate(Coordinate originalCoordinate);
int loadRes(void *data);
int capture(char replacedPiece);
_Bool isSkippedSquare (Coordinate square);
_Bool isAllowedMove (Coordinate newSquare);
_Bool isOwned(char square);
_Bool isInBounds(int row, int col);
_Bool isFirstPawnMove(int row);
_Bool isInRegion(int x, int y, int xMin, int xMax, int yMin, int yMax);

#endif