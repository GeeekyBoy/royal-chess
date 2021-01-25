/**
 * @file eventsHandler.h
 * @author GeeekyBoy
 * @brief Handlers for all mouse events used within the game.
 * \copyright Copyright 2021 GeeekyBoy Studio. All rights reserved.
    This project is released under the GNU Affero General Public License v3.
 */

#ifndef EVENTSHANDLER_H
#define EVENTSHANDLER_H

#include "definitions.h"

void handleMouseEvent(int x, int y, int btn, Uint32 type) {
  _Bool isClickable = 0;
  if (currentWindow == IN_GAME_WINDOW) {
    int row, col;
    for (row = 7; row >= 0; row--) {
      for (col = 0; col < 8; col++) {
        Coordinate currSquare = {row, col};
        Coordinate actualCoordinate = getActualCoordinate(currSquare);
        if (isInRegion(x, y, 50 + (35 * actualCoordinate.col), 50 + (35 * (actualCoordinate.col + 1)), 150 + (35 * actualCoordinate.row), 150 + (35 * (actualCoordinate.row + 1)))) {
          char clickedPiece = data.boardData[row][col];
          if (isOwned(clickedPiece)) {
            isClickable = 1;
            if (type == SDL_MOUSEBUTTONDOWN) {
              resetSelection();
              selectedSquare = currSquare;
              isMovable(selectedSquare, 0);
            }
          } else if (selectedSquare.row != -1 && selectedSquare.col != -1) {
            if (isAllowedMove(currSquare)) {
              isClickable = 1;
              if (type == SDL_MOUSEBUTTONDOWN) {
                askForMove(selectedSquare, currSquare);
              }
            }
          }
          break;
          return;
        }
      }
    }
    if (isInRegion(x, y, SAVE_BTN_X, SAVE_BTN_X + IN_GAME_BTN_W, SAVE_BTN_Y, SAVE_BTN_Y + IN_GAME_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = SAVE_WINDOW;
      }
    } else if (isInRegion(x, y, END_BTN_X, END_BTN_X + IN_GAME_BTN_W, END_BTN_Y, END_BTN_Y + IN_GAME_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = END_GAME_WINDOW;
      }
    } else if (isInRegion(x, y, UNDO_BTN_X, UNDO_BTN_X + IN_GAME_BTN_W, UNDO_BTN_Y, UNDO_BTN_Y + IN_GAME_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        if (btn == SDL_BUTTON_LEFT) {
          undo();
        } else if (btn == SDL_BUTTON_RIGHT) {
          redo();
        }
      }
    } else if (isInRegion(x, y, SCREEN_MODE_BTN_X, SCREEN_MODE_BTN_X + IN_GAME_BTN_W, SCREEN_MODE_BTN_Y, SCREEN_MODE_BTN_Y + IN_GAME_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        isFullScreen = isFullScreen ? 0 : 1;
        SDL_SetWindowFullscreen(Game.screen.window, isFullScreen);
      }
    }
  } else if (currentWindow == SAVE_WINDOW) {
    if (isInRegion(x, y, SAVE_CONFIRM_BTN_X, SAVE_CONFIRM_BTN_X + DIALOG_BTN_W, SAVE_CONFIRM_BTN_Y, SAVE_CONFIRM_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        saveGame();
        currentWindow = SAVE_COMPLETE_WINDOW;
      }
    } else if (isInRegion(x, y, SAVE_CANCEL_BTN_X, SAVE_CANCEL_BTN_X + DIALOG_BTN_W, SAVE_CANCEL_BTN_Y, SAVE_CANCEL_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = IN_GAME_WINDOW;
      }
    }
  } else if (currentWindow == DRAW_AGREEMENT) {
    if (isInRegion(x, y, DRAW_CONFIRM_BTN_X, DRAW_CONFIRM_BTN_X + DIALOG_BTN_W, DRAW_CONFIRM_BTN_Y, DRAW_CONFIRM_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        endGameByDraw();
      }
    } else if (isInRegion(x, y, DRAW_CANCEL_BTN_X, DRAW_CANCEL_BTN_X + DIALOG_BTN_W, DRAW_CANCEL_BTN_Y, DRAW_CANCEL_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = IN_GAME_WINDOW;
      }
    }
  } else if (currentWindow == SAVE_COMPLETE_WINDOW) {
    if (isInRegion(x, y, SAVE_OK_BTN_X, SAVE_OK_BTN_X + DIALOG_BTN_W, SAVE_OK_BTN_Y, SAVE_OK_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = IN_GAME_WINDOW;
      }
    }
  } else if (currentWindow == END_GAME_WINDOW) { 
    if (isInRegion(x, y, RESIGN_CONFIRM_BTN_X, RESIGN_CONFIRM_BTN_X + DIALOG_BTN_W, RESIGN_CONFIRM_BTN_Y, RESIGN_CONFIRM_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        endGameByCheckmate();
      }
    } else if (isInRegion(x, y, DRAW_OFFER_BTN_X, DRAW_OFFER_BTN_X + DIALOG_BTN_W, DRAW_OFFER_BTN_Y, DRAW_OFFER_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = DRAW_AGREEMENT;
      }
    } else if (isInRegion(x, y, EXIT_CONFIRM_BTN_X, EXIT_CONFIRM_BTN_X + DIALOG_BTN_W, EXIT_CONFIRM_BTN_Y, EXIT_CONFIRM_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = MAIN_MENU;
        resetUndoData();
        resetLogTxt();
        resetSelection();
      }
    } else if (isInRegion(x, y, END_CANCEL_BTN_X, END_CANCEL_BTN_X + DIALOG_BTN_W, END_CANCEL_BTN_Y, END_CANCEL_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        currentWindow = IN_GAME_WINDOW;
      }
    }
  } else if (currentWindow == PROMOTION_WINDOW) {
    _Bool isPromoted = 0;
    if (isInRegion(x, y, BISHOP_PROMOTION_BTN_X, BISHOP_PROMOTION_BTN_X + PROMOTION_BTN_WH, PROMOTION_BTN_Y, PROMOTION_BTN_Y + PROMOTION_BTN_WH)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        data.boardData[promotedPieceSquare.row][promotedPieceSquare.col] = getRightPiece('b', 0);
        isPromoted = 1;
      }
    } else if (isInRegion(x, y, KNIGHT_PROMOTION_BTN_X, KNIGHT_PROMOTION_BTN_X + PROMOTION_BTN_WH, PROMOTION_BTN_Y, PROMOTION_BTN_Y + PROMOTION_BTN_WH)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        data.boardData[promotedPieceSquare.row][promotedPieceSquare.col] = getRightPiece('n', 0);
        isPromoted = 1;
      }
    } else if (isInRegion(x, y, QUEEN_PROMOTION_BTN_X, QUEEN_PROMOTION_BTN_X + PROMOTION_BTN_WH, PROMOTION_BTN_Y, PROMOTION_BTN_Y + PROMOTION_BTN_WH)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        data.boardData[promotedPieceSquare.row][promotedPieceSquare.col] = getRightPiece('q', 0);
        isPromoted = 1;
      }
    } else if (isInRegion(x, y, ROOK_PROMOTION_BTN_X, ROOK_PROMOTION_BTN_X + PROMOTION_BTN_WH, PROMOTION_BTN_Y, PROMOTION_BTN_Y + PROMOTION_BTN_WH)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        data.boardData[promotedPieceSquare.row][promotedPieceSquare.col] = getRightPiece('r', 0);
        isPromoted = 1;
      }
    }
    if (isPromoted) {
      currentWindow = IN_GAME_WINDOW;
      setPlayerState();
      applyPlayerState();
      appednAlgebraicNotation(1);
      if (data.playerState == NONE) {
        Mix_ChannelFinished(NULL);
        Mix_HaltChannel(-1);
        Mix_PlayChannel(-1, promotionSound, 0);
      }
    }
  } else if (currentWindow == MAIN_MENU) {
    if (isInRegion(x, y, MAIN_MENU_BTN_X, MAIN_MENU_BTN_X + DIALOG_BTN_W, NEW_GAME_BTN_Y, NEW_GAME_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(startGameSound);
        newGame();
        currentWindow = IN_GAME_WINDOW;
      }
    } else if (isInRegion(x, y, MAIN_MENU_BTN_X, MAIN_MENU_BTN_X + DIALOG_BTN_W, LOAD_GAME_BTN_Y, LOAD_GAME_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(startGameSound);
        loadGame();
        currentWindow = IN_GAME_WINDOW;
      }
    } else if (isInRegion(x, y, MAIN_MENU_BTN_X, MAIN_MENU_BTN_X + DIALOG_BTN_W, EXIT_GAME_BTN_Y, EXIT_GAME_BTN_Y + DIALOG_BTN_H)) {
      isClickable = 1;
      if (type == SDL_MOUSEBUTTONDOWN) {
        playSound(clickSound);
        Game.running = SDL_FALSE;
      }
    }
  }
  if (isClickable)
    SDL_SetCursor(handCursor);
  else
    SDL_SetCursor(arrowCursor);
}

void handleMousewheelEvent(int x, int y, int steps) {
  if (currentWindow == IN_GAME_WINDOW) {
    if (isInRegion(x, y, 420, 580, 380, 440)) {
      int propsedScrollPos = logScrollPos + (steps * 10) / -1;
      if (propsedScrollPos > logHeight - 60 * screenScale)
        logScrollPos = logHeight - 60 * screenScale;
      else if (propsedScrollPos < 0)
        logScrollPos = 0;
      else
        logScrollPos = propsedScrollPos;
    }
  }
}

#endif