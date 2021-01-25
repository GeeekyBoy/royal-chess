/**
 * @file render.h
 * @author GeeekyBoy
 * @brief Game frames rendering
 * \copyright Copyright 2021 GeeekyBoy Studio. All rights reserved.
    This project is released under the GNU Affero General Public License v3.
 */

#ifndef RENDER_H
#define RENDER_H

#include "definitions.h"

/**
 *  \brief Render given chess piece within the given region on the screen.
 *
 *  \param piece Case-sensitive character representing piece to be rendered.
 *  \param x X coordinate of the piece on the screen
 *  \param y Y coordinates of the piece on the screen
 *  \param isSmall 1 if the piece will be placed in the inventory
 *                 of the captured pieces. 0 if otherwise
 *
 *  \sa renderPiece
 */
static void renderPiece(char piece, int x, int y, _Bool isSmall);
/**
 *  \brief render image within the given region on the screen.
 *
 *  \param imgInfo Information of the image to be rendered
 *  \param x X coordinate of the image on the screen
 *  \param y Y coordinates of the image on the screen
 *  \param isReveredBoard 1 if the image is a rotated chess board.
 *                        0 if otherwise
 *
 *  \sa renderSVG
 */
static void renderSVG(Image imgInfo, int x, int y, _Bool isReveredBoard);
/**
 *  \brief render static text within the given region on the screen.
 *
 *  \param txtData Information of the image containing text to be rendered
 *  \param x X coordinate of the text on the screen
 *  \param y Y coordinates of the text on the screen
 *
 *  \sa drawTxt
 */
static void drawTxt(Image txtData, int x, int y);
/**
 *  \brief render scrollable text within the given region on the screen.
 *
 *  \param txtData Information of the image containing text to be rendered
 *  \param x X coordinate of the text on the screen
 *  \param y Y coordinates of the text on the screen
 *  \param width Width of the text container
 *  \param height Height of the text container
 *
 *  \sa drawScrollTxt
 */
static void drawScrollTxt(Image txtData, int x, int y, int width, int height);

static void renderPiece(char piece, int x, int y, _Bool isSmall) {
     switch (piece)
    {
    case 'k':
        renderSVG(isSmall ? kingSmallTile : kingTile, x, y, 0);
        break;
    case 'r':
        renderSVG(isSmall ? rookSmallTile : rookTile, x, y, 0);
        break;
    case 'q':
        renderSVG(isSmall ? queenSmallTile : queenTile, x, y, 0);
        break;
    case 'b':
        renderSVG(isSmall ? bishopSmallTile : bishopTile, x, y, 0);
        break;
    case 'n':
        renderSVG(isSmall ? knightSmallTile : knightTile, x, y, 0);
        break;
    case 'p':
        renderSVG(isSmall ? pawnSmallTile : pawnTile, x, y, 0);
        break;
    case 'K':
        renderSVG(isSmall ? kingDarkSmallTile : kingDarkTile, x, y, 0);
        break;
    case 'R':
        renderSVG(isSmall ? rookDarkSmallTile : rookDarkTile, x, y, 0);
        break;
    case 'Q':
        renderSVG(isSmall ? queenDarkSmallTile : queenDarkTile, x, y, 0);
        break;
    case 'B':
        renderSVG(isSmall ? bishopDarkSmallTile : bishopDarkTile, x, y, 0);
        break;
    case 'N':
        renderSVG(isSmall ? knightDarkSmallTile : knightDarkTile, x, y, 0);
        break;
    case 'P':
        renderSVG(isSmall ? pawnDarkSmallTile : pawnDarkTile, x, y, 0);
        break;
    }
}

static void drawTxt(Image txtData, int x, int y) {
  SDL_Rect logTxtRect = {(x * screenScale) - (txtData.width / 2), (y * screenScale) - (txtData.height / 2), txtData.width, txtData.height};
  SDL_RenderFillRect(Game.screen.renderer, &logTxtRect);
  SDL_RenderCopy(Game.screen.renderer, txtData.tex, NULL, &logTxtRect);
}

Image mkTxt(char *txt, TTF_Font *font, SDL_Color color, int maxWidth) {
    Image txtData;
    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, txt, color, maxWidth * screenScale);
    txtData.tex = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(txtData.tex, NULL, NULL, &txtData.width, &txtData.height);
    return txtData;
}

void updateLogTxt() {
    char *algebraicNotation = getAlgebraicLog();
    resetLogTxt();
    logTxt = mkTxt(algebraicNotation, robotoBold, brownTxtColor, 160);
    free(algebraicNotation);
    if (logHeight - 60 * screenScale >= 0)
        logScrollPos = logHeight - 60 * screenScale;
}

static void drawScrollTxt(Image txtData, int x, int y, int width, int height) {
  SDL_Rect txtRect;
  SDL_Rect logTxtRect;
  logHeight = txtData.height;
  if (txtData.height <= height * screenScale) {
    txtRect = (SDL_Rect){0, 0, txtData.width, txtData.height};
    logTxtRect = (SDL_Rect){x * screenScale, y * screenScale, txtData.width, txtData.height};
  } else {
    txtRect = (SDL_Rect){0, 0 + logScrollPos, txtData.width, height * screenScale};
    logTxtRect = (SDL_Rect){x * screenScale, y * screenScale, txtData.width, height * screenScale};
  }
  SDL_RenderFillRect(Game.screen.renderer, &logTxtRect);
  SDL_RenderCopy(Game.screen.renderer, txtData.tex, &txtRect, &logTxtRect);
}

static void renderSVG(Image imgInfo, int x, int y, _Bool isReveredBoard) {
  SDL_Rect imgContainer = {x * screenScale, y * screenScale, imgInfo.width, imgInfo.height};
  SDL_SetRenderDrawBlendMode(Game.screen.renderer, SDL_BLENDMODE_BLEND);
  SDL_RenderFillRect(Game.screen.renderer, &imgContainer);
  SDL_RenderCopyEx(Game.screen.renderer, imgInfo.tex, NULL, &imgContainer, isReveredBoard ? 180 : 0, NULL, SDL_FLIP_NONE);
}

void applyPlayerState() {
  if (data.playerState != NONE) {
    if (data.playerState == CHECK) {
      playSound(checkSound);
      Mix_ChannelFinished(playWarningSound);
    } else if (data.playerState == CHECKMATE) {
      playSound(checkmateSound);
      Mix_ChannelFinished(endGameByCheckmate);
    } else if (data.playerState == STALEMATE) {
      playSound(stalemateSound);
      Mix_ChannelFinished(endGameByDraw);
    } else if (data.playerState == DEAD_POSITION) {
      playSound(deadPositionSound);
      Mix_ChannelFinished(endGameByDraw);
    }
  }
}

void renderFrame() {
    if (currentWindow == IN_GAME_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(board, 20, 120, data.player == 1 ? 0 : 1);
        renderSVG(saveGameBtn, SAVE_BTN_X, SAVE_BTN_Y, 0);
        renderSVG(endGameBtn, END_BTN_X, END_BTN_Y, 0);
        renderSVG(undoBtn, UNDO_BTN_X, UNDO_BTN_Y, 0);
        renderSVG(isFullScreen ? windowedBtn : fullscreenBtn, SCREEN_MODE_BTN_X, SCREEN_MODE_BTN_Y, 0);
        renderSVG(data.player == 1 ? playerOneTile : playerTwoTile, 124, 20, 0);
        int row, col, i;
        for (row = 7; row >= 0; row--) {
            for (col = 0; col < 8; col++) {
                Coordinate actualCoordinate = getActualCoordinate((Coordinate){row, col});
                _Bool isDark = ((row + 1) + (col + 1)) % 2 == 0;
                renderSVG(isDark ? darkTile : lightTile, 50 + 35 * actualCoordinate.col, 150 + 35 * actualCoordinate.row, 0);
                if (selectedSquare.row == row && selectedSquare.col == col) {
                    renderSVG(selectedTile, 50 + 35 * actualCoordinate.col, 150 + 35 * actualCoordinate.row, 0);
                }
                if (data.boardData[row][col] != DUMP_PIECE) {
                    renderPiece(data.boardData[row][col], 50 + 35 * actualCoordinate.col, 150 + 35 * actualCoordinate.row, 0);
                }
            }
        }
        for (i = 0;i < allowedSquaresNum;i++) {
            Coordinate actualCoordinate = getActualCoordinate(allowedSquares[i]);
            renderSVG(allowedTile, 50 + 35 * actualCoordinate.col, 150 + 35 * actualCoordinate.row, 0);
        }
        renderSVG(playerTwoCaptured, 380, 20, 0);
        renderSVG(playerOneCaptured, 380, 190, 0);
        renderSVG(logTile, 380, 360, 0);
        if (data.capturedNum[1] > 0) {
            for (i = 0; i < data.capturedNum[1]; i++) {
            renderPiece(data.capturedPieces[1][i], 420 + 20 * (i > 7 ? i - 8 : i), (i > 7 ? 115 : 95), 1);
            }
        } else {
            drawTxt(noCapturedTxt, 500, 118);
        }
        if (data.capturedNum[0] > 0) {
            for (i = 0; i < data.capturedNum[0]; i++) {
                renderPiece(data.capturedPieces[0][i], 420 + 20 * (i > 7 ? i - 8 : i), (i > 7 ? 285 : 265), 1);
            }
        } else {
            drawTxt(noCapturedTxt, 500, 288);
        }
        if (logTxt.tex != NULL)
            drawScrollTxt(logTxt, 420, 380, 160, 60);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == PROMOTION_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(promotionDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == DRAW_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(drawDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == PLAYER_ONE_VICTORY_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(playerOneVictoryDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == PLAYER_TWO_VICTORY_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(playerTwoVictoryDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == SAVE_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(saveGameDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == DRAW_AGREEMENT) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(drawAgreementDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == SAVE_COMPLETE_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(saveConfirmedDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == END_GAME_WINDOW) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(endGameDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
    } else if (currentWindow == MAIN_MENU) {
      if (texInitState == 2) {
        SDL_RenderClear(Game.screen.renderer);
        renderSVG(gameBackgroundTile, 0, 0, 0);
        renderSVG(mainMenuDialog, 0, 0, 0);
        SDL_RenderPresent(Game.screen.renderer);
      } else if (texInitState == 0) {
        if (splashDialog.tex != NULL) {
            SDL_RenderClear(Game.screen.renderer);
            renderSVG(splashDialog, 0, 0, 0);
            SDL_RenderPresent(Game.screen.renderer);
            SDL_DestroyTexture(splashDialog.tex);
            splashDialog.tex = NULL;
            texInitState = 1;
            SDL_CreateThread(loadRes, "loadRes", NULL);
        }
      }
    }
}

#endif