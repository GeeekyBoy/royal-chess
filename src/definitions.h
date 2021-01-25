/**
 * @file definitions.h
 * @author GeeekyBoy
 * @brief Definitions of every constant or global variable used within the game.
 * \copyright Copyright 2021 GeeekyBoy Studio. All rights reserved.
    This project is released under the GNU Affero General Public License v3.
 */

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

_Bool isFullScreen = 1;

GameWindow currentWindow = MAIN_MENU;

/**
 *  \brief Update the position of the moving king if any.
 *
 *  \param square piece that is being moved
 *  \param newCoordinate Coordinates of the destination
 *
 *  \sa updateKingPos
 */
void updateKingPos(char square, Coordinate newCoordinate);
/**
 *  \brief Toggle current player.
 *
 *  \sa switchPlayer
 */
void switchPlayer();
/**
 *  \brief Bring the new player state into effect
 *         like saying checkmate then showing victory window
 *         in case of checkmate.
 *
 *  \sa applyPlayerState
 */
void applyPlayerState();
/**
 *  \brief Render the whole frame.
 *
 *  \sa renderFrame
 */
void renderFrame();
/**
 *  \brief Start a new game.
 *
 *  \sa newGame
 */
void newGame();
/**
 *  \brief Save current game to be loaded later.
 *         This overwrites any current saved games.
 *
 *  \sa saveGame
 */
void saveGame();
/**
 *  \brief Reset current piece selection.
 *
 *  \sa resetSelection
 */
void resetSelection();
/**
 *  \brief Load an already saved game if any.
 *         Start a new game if no saved games found.
 *
 *  \sa loadGame
 */
void loadGame();
/**
 *  \brief The main initializer for SDL2.
 *
 *  \sa game_init
 */
void game_init(void);
/**
 *  \brief Do all actions required before exiting game.
 *
 *  \sa game_quit
 */
void game_quit(void);
/**
 *  \brief Reinitialization of the captured pieces
 *         inventory for both players.
 *
 *  \sa resetCapturedPiecesInventory
 */
void resetCapturedPiecesInventory();
/**
 *  \brief Destroy the entire history.
 *         Required before starting a new game.
 *
 *  \sa resetUndoData
 */
void resetUndoData();
/**
 *  \brief Destroy any texture stored in memory.
 *         Required before exiting the game.
 *
 *  \sa resetTextures
 */
void resetTextures();
/**
 *  \brief Destroy any font stored in memory.
 *         Required before exiting the game.
 *
 *  \sa resetFonts
 */
void resetFonts();
/**
 *  \brief Fires a dump event to force rendering the next frame.
 *
 *  \sa fireDumpEvent
 */
void fireDumpEvent();
/**
 *  \brief Destroy any audio data stored in memory.
 *         Required before exiting the game.
 *
 *  \sa resetAudio
 */
void resetAudio();
/**
 *  \brief Save PGN file of any proper ended game.
 *
 *  \sa savePGN
 */
void savePGN();
/**
 *  \brief Updates the texture of algebraic notation.
 *         Required because rendering wrapped text on every
 *         frame consumes much resources.
 *
 *  \sa updateLogTxt
 */
void updateLogTxt();
/**
 *  \brief Go to main menu.
 *
 *  \sa goToMainMenu
 */
void goToMainMenu();
/**
 *  \brief End game by checkmate.
 *         Called by applyPlayerState().
 *
 *  \sa endGameByCheckmate
 */
void endGameByCheckmate();
/**
 *  \brief End game by draw.
 *         Called by applyPlayerState().
 *
 *  \sa endGameByCheckmate
 */
void endGameByDraw();
/**
 *  \brief Play warning sound.
 *         Called by applyPlayerState() in case of check.
 *
 *  \sa playWarningSound
 */
void playWarningSound();
/**
 *  \brief Clear the log of algebraic notations
 *
 *  \sa resetLogTxt
 */
void resetLogTxt();
/**
 *  \brief Creates saved and pgn folders if they do not exist.
 *
 *  \sa getMissingFiles
 */
void getMissingFiles();
/**
 *  \brief Play a sound after halting the playing one.
 *
 *  \param sound Pointer to the sound to be played
 *
 *  \sa playSound
 */
void playSound(Mix_Chunk* sound);
/**
 *  \brief Do actions depending on mouse motion or click.
 *
 *  \param x Mouse pointer X coordinate
 *  \param y Mouse pointer Y coordinate
 *  \param btn Clicked Mouse button
 *  \param type Mouse event type
 *
 *  \sa handleMouseEvent
 */
void handleMouseEvent(int x, int y, int btn, Uint32 type);
/**
 *  \brief Do actions depending on scrolling mouse wheel.
 *         Used to scroll the text of algebraic notation.
 *
 *  \param x Mouse pointer X coordinate
 *  \param y Mouse pointer Y coordinate
 *  \param steps Signed steps of scrolling.
 *
 *  \sa handleMousewheelEvent
 */
void handleMousewheelEvent(int x, int y, int steps);
/**
 *  \brief Construct the algebraic notation of the most recent move
 *         and append it to its data.
 *
 *  \param isPromoted 1 if promotion occured, 0 if otherwise
 *
 *  \sa appednAlgebraicNotation
 */
void appednAlgebraicNotation(_Bool isPromoted);
/**
 *  \brief Get algebraic notation of the whole game
 *         formatted as one string.
 * 
 *  \return A string containing the notation
 *
 *  \sa getAlgebraicLog
 */
char* getAlgebraicLog();
/**
 *  \brief Asks player to do promotion if applies.
 *
 *  \param firstSquare Square from which the piece will move
 *  \param secondSquare The destination of the moving piece
 *  \param isRedo 1 if the current move is redoing of an undone move,
 *                0 if otherwise
 *
 *  \sa doPromotion
 */
void doPromotion(Coordinate firstSquare, Coordinate secondSquare, _Bool isRedo);
/**
 *  \brief Check if moving piece standing on the first square
 *         to the second square will result in a self-check or not.
 *         Cloned chess piece is used in this process.
 *
 *  \param firstSquare Square from the piece will move
 *  \param secondSquare The destination of the moving piece
 *  \return 1 if move is prohibited, 0 if otherwise
 *
 *  \sa isToBeChecked
 */
_Bool isToBeChecked(Coordinate firstSquare, Coordinate secondSquare);
/**
 *  \brief Show possible moves of the piece standing on the square
 *         having the given coordinates.
 *
 *  \param coordinate Coordinates of the square
 *  \param isInternal 1 if we want to only check
 *                    if there is at least one possible
 *                    move without showing any thing,
 *                    0 if otherwise
 *  \return 1 if piece is movable, 0 if otherwise
 *
 *  \sa isMovable
 */
_Bool isMovable(Coordinate coordinate, _Bool isInternal);
/**
 *  \brief Do castling if applies.
 *
 *  \param firstSquare Square from which the piece will move
 *  \param secondSquare The destination of the moving piece
 *  \param isUndo 1 if the current move is undoing of a done move,
 *                0 if otherwise
 *
 *  \sa doCastling
 */
void doCastling(Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo);
/**
 *  \brief Do En Passant move if applies.
 *
 *  \param firstSquare Square from which the piece will move
 *  \param secondSquare The destination of the moving piece
 *  \param isUndo 1 if the current move is undoing of a done move,
 *                0 if otherwise
 *
 *  \sa doEnpassant
 */
void doEnpassant (Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo);
/**
 *  \brief The main trigger for pieces moving.
 *         It does nothing but ORGANIZES
 *         the whole process of moving.
 *
 *  \param firstSquare Square from which the piece will move
 *  \param secondSquare The destination of the moving piece
 *
 *  \sa askForMove
 */
void askForMove(Coordinate firstSquare, Coordinate secondSquare);
/**
 *  \brief Modify the list of pieces qualified for castling.
 *         Only makes sense in case the moved piece is king
 *         or rook moving from its initial place.
 *
 *  \param coordinate The coordinates of the moving piece
 *
 *  \sa setCastlingState
 */
void setCastlingState (Coordinate coordinate);
/**
 *  \brief Update the square skipped by the moving
 *         pawn during the last move.
 *         A pawn can skip a square through
 *         moving 2 steps forward.
 *         Only makes sense in case the moved piece is a pawn
 *         moving 2 steps forward.
 *
 *  \param firstSquare The coordinates of the moving piece
 *  \param secondSquare The destination of the moving piece
 *
 *  \sa setEnPassantData
 */
void setEnPassantData (Coordinate firstSquare, Coordinate secondSquare);

/**
 *  \brief Append the information of the current move to the history.
 *
 *  \param firstPiece Moving piece
 *  \param firstSquare The initial position of the moving piece
 *  \param secondPiece The piece existing in the destination of the moving piece
 *  \param secondSquare The destination of the moving piece
 *  \param capturedPlayer Player captured during this move. Equals 0 if no players captured.
 *
 *  \sa addUndoData
 */
void addUndoData(char firstPiece, Coordinate firstSquare, char secondPiece,
                 Coordinate secondSquare, int capturedPlayer);
/**
 *  \brief Undo the last move if any.
 *
 *  \sa undo
 */
void undo();
/**
 *  \brief Redo the next undone move if any.
 *
 *  \sa redo
 */
void redo();
/**
 *  \brief Get the character representation of a specific piece
 *         owned by the given player.
 *
 *  \param square Not case-sensitive character representing the piece
 *  \param isOwned 1 if the required piece is owned by current player,
 *                 0 if it is owned by his/her opponent.
 *  \return Character representing the piece in question
 *
 *  \sa getRightPiece
 */
char getRightPiece(char square, _Bool isOwned);
/**
 *  \brief Get absolute file path of the given relative file path.
 *
 *  \param relPath String containing path relative
 *                 to the executable file of the game
 *  \return String containing the absolute path
 *
 *  \sa getAbsPath
 */
char *getAbsPath(char *relPath);
/**
 *  \brief Convert SVG included resource into texture.
 *         Width & Height of the texture are included
 *         with the texture inside a constructor of Image
 *         data type.
 *
 *  \param svgData Data of the included SVG resource
 *  \return A constructor holding all information of the texture
 *
 *  \sa svg2tex
 */
Image svg2tex(char *svgData);
/**
 *  \brief Generate a texture holding the given text.
 *
 *  \param txt String containing the needed text
 *  \param font A pointer to the font in which text will be written
 *  \param color Color of the text
 *  \param maxWidth Maximum width of the text.
 *                  Usually, its value is like that of the width
 *                  of the text container
 *  \return A constructor holding all information of the texture
 *
 *  \sa mkTxt
 */
Image mkTxt(char *txt, TTF_Font *font, SDL_Color color, int maxWidth);
/**
 *  \brief Get the increment of row and column in the given direction
 *
 *  \param directionID ID indicating the required direction.
 *                     It may be one of the follwoing 16 values:
 *                     Direction 1: Diagonally (+X, +Y)
 *                     Direction 2: Diagonally (-X, -Y)
 *                     Direction 3: Diagonally (-X, +Y)
 *                     Direction 4: Diagonally (+X, -Y)
 *                     Direction 5: Straight (+Y)
 *                     Direction 6: Straight (-Y)
 *                     Direction 7: Straight (+X)
 *                     Direction 8: Straight (-X)
 *                     Direction 9:16: All 8 L-shaped movements.
 *  \return Delta coordinate representing the given direction
 *
 *  \sa getDirection
 */
Coordinate getDirection(int directionID);
/**
 *  \brief Get actual coordinate of the piece.
 *         Only make sense in case that chess board is rotated.
 *
 *  \param originalCoordinate Coordinate of the piece on the non-rotated board.
 *                            (aka. Index of the piece in the board 8x8 matrix)
 *  \return Coordinate representing the actual coordinate of the piece within the bounds of the board
 *
 *  \sa getActualCoordinate
 */
Coordinate getActualCoordinate(Coordinate originalCoordinate);
/**
 *  \brief Initialization of the process of loading game resources.
 *         Called in a new thread to prevent game hang while loading.
 * 
 *  \sa loadRes
 */
int loadRes(void *data);
/**
 *  \brief Append the captured piece to the appropriate inventory.
 *
 *  \param replacedPiece Character representing the captured piece
 *  \return ID of the player whose piece is captured.
 *          0 if there is no captured pieces.
 *
 *  \sa capture
 */
int capture(char replacedPiece);
/**
 *  \brief Check if the given square is skipped by a pawn during
 *         the last move or not. Used as a mean of En Passant move validation.
 *
 *  \param square Coordinates of the square in question
 *  \return 1 if square is skipped, 0 if otherwise
 *
 *  \sa isSkippedSquare
 */
_Bool isSkippedSquare(Coordinate square);
/**
 *  \brief Check if the given square is a valid destination for
 *         current selected piece or not. Used by the mouse event
 *         handler to do the suitable action on clicking a square.
 *
 *  \param newSquare Coordinates of the square in question
 *  \return 1 if square is a valid destination, 0 if otherwise
 *
 *  \sa isAllowedMove
 */
_Bool isAllowedMove(Coordinate newSquare);
/**
 *  \brief Check if the given piece is owned by current player or not.
 *         It works through checking the case of the letter representing
 *         the piece.
 *
 *  \param square Character representing the piece in question
 *  \return 1 if piece is owned by current player, 0 if otherwise
 *
 *  \sa isOwned
 */
_Bool isOwned(char square);
/**
 *  \brief Check if the given coordinates represents a square existing
 *         on the chess board or not. Used in direction-based searching techniques.
 *
 *  \param square Character representing the piece in question
 *  \return 1 if square exists on board, 0 if otherwise
 *
 *  \sa isInBounds
 */
_Bool isInBounds(int row, int col);
/**
 *  \brief Check if a specific pawn stands on its initial position or not.
 *         Used to determine if the pawn can move 2 steps forward or not.
 *
 *  \param row Row where pawn in question stands
 *  \return 1 if pawn stands in its initial position, 0 if otherwise
 *
 *  \sa isFirstPawnMove
 */
_Bool isFirstPawnMove(int row);
/**
 *  \brief Check if the mouse pointer exists within a specific region or not.
 *         Used by the event handler to decide which button is actually clicked.
 *
 *  \param x X coordinate of the mouse pointer
 *  \param y Y coordinate of the mouse pointer
 *  \param xMin Minimum X coordinate of region in question
 *  \param xMax Maximum X coordinate of region in question
 *  \param yMin Minimum Y coordinate of region in question
 *  \param yMax Maximum Y coordinate of region in question
 *  \return 1 if mouse pointer exists within region in question, 0 if otherwise
 *
 *  \sa isInRegion
 */
_Bool isInRegion(int x, int y, int xMin, int xMax, int yMin, int yMax);

#endif