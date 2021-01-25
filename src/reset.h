/**
 * @file reset.h
 * @author GeeekyBoy
 * @brief Reset different stuff within the game.
 *        Used commonly when starting a game, ending a game
 *        or exiting the whole program
 * \copyright Copyright 2021 GeeekyBoy Studio. All rights reserved.
    This project is released under the GNU Affero General Public License v3.
 */

#ifndef RESET_H 
#define RESET_H

#include "definitions.h"

void resetUndoData() {
  free(data.undoData);
  data.undoData = malloc(0 * sizeof(Step));
  data.undoDataSize = 0;
}

void resetSelection() {
  selectedSquare = (Coordinate){-1, -1};
  allowedSquaresNum = 0;
}

void resetTextures() {
  SDL_DestroyTexture(gameBackgroundTile.tex);
  SDL_DestroyTexture(drawDialog.tex);
  SDL_DestroyTexture(mainMenuDialog.tex);
  SDL_DestroyTexture(playerOneVictoryDialog.tex);
  SDL_DestroyTexture(playerTwoVictoryDialog.tex);
  SDL_DestroyTexture(drawAgreementDialog.tex);
  SDL_DestroyTexture(saveGameDialog.tex);
  SDL_DestroyTexture(saveConfirmedDialog.tex);
  SDL_DestroyTexture(promotionDialog.tex);
  SDL_DestroyTexture(endGameDialog.tex);
  SDL_DestroyTexture(saveGameBtn.tex);
  SDL_DestroyTexture(endGameBtn.tex);
  SDL_DestroyTexture(undoBtn.tex);
  SDL_DestroyTexture(windowedBtn.tex);
  SDL_DestroyTexture(fullscreenBtn.tex);
  SDL_DestroyTexture(board.tex);
  SDL_DestroyTexture(playerOneCaptured.tex);
  SDL_DestroyTexture(playerTwoCaptured.tex);
  SDL_DestroyTexture(selectedTile.tex);
  SDL_DestroyTexture(allowedTile.tex);
  SDL_DestroyTexture(logTile.tex);
  SDL_DestroyTexture(playerOneTile.tex);
  SDL_DestroyTexture(playerTwoTile.tex);
  SDL_DestroyTexture(darkTile.tex);
  SDL_DestroyTexture(lightTile.tex);
  SDL_DestroyTexture(kingTile.tex);
  SDL_DestroyTexture(rookTile.tex);
  SDL_DestroyTexture(queenTile.tex);
  SDL_DestroyTexture(bishopTile.tex);
  SDL_DestroyTexture(knightTile.tex);
  SDL_DestroyTexture(pawnTile.tex);
  SDL_DestroyTexture(kingDarkTile.tex);
  SDL_DestroyTexture(rookDarkTile.tex);
  SDL_DestroyTexture(queenDarkTile.tex);
  SDL_DestroyTexture(bishopDarkTile.tex);
  SDL_DestroyTexture(knightDarkTile.tex);
  SDL_DestroyTexture(pawnDarkTile.tex);
  SDL_DestroyTexture(kingSmallTile.tex);
  SDL_DestroyTexture(rookSmallTile.tex);
  SDL_DestroyTexture(queenSmallTile.tex);
  SDL_DestroyTexture(bishopSmallTile.tex);
  SDL_DestroyTexture(knightSmallTile.tex);
  SDL_DestroyTexture(pawnSmallTile.tex);
  SDL_DestroyTexture(kingDarkSmallTile.tex);
  SDL_DestroyTexture(rookDarkSmallTile.tex);
  SDL_DestroyTexture(queenDarkSmallTile.tex);
  SDL_DestroyTexture(bishopDarkSmallTile.tex);
  SDL_DestroyTexture(knightDarkSmallTile.tex);
  SDL_DestroyTexture(pawnDarkSmallTile.tex);
  resetLogTxt();
}

void resetFonts() {
    TTF_CloseFont(robotoBold);
}

void resetLogTxt() {
  if (logTxt.tex != NULL) {
    SDL_DestroyTexture(logTxt.tex);
    logTxt.tex = NULL;
  }
}

void resetAudio() {
    Mix_FreeChunk(moveSound);
    Mix_FreeChunk(checkSound);
    Mix_FreeChunk(checkmateSound);
    Mix_FreeChunk(stalemateSound);
    Mix_FreeChunk(victorySound);
    Mix_FreeChunk(promotionSound);
    Mix_FreeChunk(drawSound);
    Mix_FreeChunk(warningSound);
    Mix_FreeChunk(deadPositionSound);
    Mix_FreeChunk(promotionSound);
    Mix_FreeChunk(undoSound);
    Mix_FreeChunk(redoSound);
    Mix_FreeChunk(errorSound);
    Mix_FreeChunk(clickSound);
    Mix_FreeChunk(startGameSound);
}

#endif