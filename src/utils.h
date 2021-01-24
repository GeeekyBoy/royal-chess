#ifndef UTILS_H
#define UTILS_H

#include "definitions.h"

char* getPath(char *relPath) {
    char *absPath = SDL_GetBasePath();
    strcat(absPath, relPath);
    return absPath;
}

_Bool isOwned(char square) {
  if (data.player == 1 && islower(square)) {
    return 1;
  } else if (data.player == 2 && isupper(square)) {
    return 1;
  } else {
    return 0;
  }
}

_Bool isInBounds(int row, int col) {
  if (row >= 0 && row <= 7 && col >= 0 && col <= 7) {
    return 1;
  } else {
    return 0;
  }
}

char getRightPiece(char square, _Bool isOwned) {
  if (isOwned) {
    return data.player == 1 ? tolower(square) : toupper(square);
  } else {
    return data.player == 2 ? tolower(square) : toupper(square);
  }
}

_Bool isInRegion(int x, int y, int xMin, int xMax, int yMin, int yMax) {
    if (x / screenScale >= xMin && x / screenScale <= xMax && y / screenScale >= yMin && y / screenScale <= yMax) {
        return 1;
    } else {
        return 0;
    }
}

_Bool isFirstPawnMove(int row) {
  if (data.player == 1 && row == 1) {
    return 1;
  } else if (data.player == 2 && row == 6) {
    return 1;
  } else {
    return 0;
  }
}

void updateKingPos(char square, Coordinate newCoordinate) {
  if (square == 'k') {
    data.kingPos[0] = newCoordinate;
  } else if (square == 'K') {
    data.kingPos[1] = newCoordinate;
  }
}

void setCastlingState (Coordinate coordinate) {
  char movedPiece = data.boardData[coordinate.row][coordinate.col];
  if (movedPiece == getRightPiece('k', 1)) {
    data.castlingData[data.player - 1][1] = 0;
  } else if (movedPiece == getRightPiece('r', 1)) {
    if (coordinate.col == 0) {
      data.castlingData[data.player - 1][0] = 0;
    } else if (coordinate.col == 7) {
      data.castlingData[data.player - 1][2] = 0;
    }
  }
}

void setEnPassantData (Coordinate firstSquare, Coordinate secondSquare) {
	data.enPassantData = (Coordinate){-1, -1};
  char movedPiece = data.boardData[firstSquare.row][firstSquare.col];
  if (movedPiece == getRightPiece('p', 1)) {
    if (abs(firstSquare.row - secondSquare.row) == 2) {
      data.enPassantData = (Coordinate){firstSquare.row + (data.player == 1 ? 1 : -1), firstSquare.col};
    }
  }
}

void doCastling(Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo) {
  char movedPiece = data.boardData[firstSquare.row][firstSquare.col];
  int colDiff = abs(firstSquare.col - secondSquare.col);
  if (movedPiece == getRightPiece('k', 1) && colDiff > 1) {
      Coordinate oldCastleCoordinate = (Coordinate){data.player == 1 ? 0 : 7, colDiff == 2 ? 7 : 0};
      Coordinate newCastleCoordinate = (Coordinate){data.player == 1 ? 0 : 7, colDiff == 2 ? 5 : 2};
    char* firstPiece =
        &data.boardData[oldCastleCoordinate.row][oldCastleCoordinate.col];
    char* secondPiece =
        &data.boardData[newCastleCoordinate.row][newCastleCoordinate.col];
    if (isUndo) {
      *firstPiece = *secondPiece;
      *secondPiece = DUMP_PIECE;
    } else {
      *secondPiece = *firstPiece;
      *firstPiece = DUMP_PIECE;
    }
  }
}

void doEnpassant (Coordinate firstSquare, Coordinate secondSquare, _Bool isUndo) {
    char movedPiece = data.boardData[firstSquare.row][firstSquare.col];
    int colDiff = abs(firstSquare.col - secondSquare.col);
    if (movedPiece == getRightPiece('p', 1) && colDiff == 1) {
    if (data.boardData[secondSquare.row][secondSquare.col] == DUMP_PIECE) {
      Coordinate skippingPawnSquare = {firstSquare.row, secondSquare.col};
      if (isUndo) {
        data.boardData[skippingPawnSquare.row][skippingPawnSquare.col] = getRightPiece('p', 0);
        data.capturedNum[abs(data.player - 2)]--;
      } else {
        data.boardData[skippingPawnSquare.row][skippingPawnSquare.col] = DUMP_PIECE;
        capture(getRightPiece('p', 0));
      }
    }
  }
}

void doPromotion (Coordinate firstSquare, Coordinate secondSquare, _Bool isRedo) {
    char* movedPiece = &data.boardData[firstSquare.row][firstSquare.col];
    _Bool shouldPromote = secondSquare.row == 7 || secondSquare.row == 0 ? 1 : 0;
    if (*movedPiece == getRightPiece('p', 1) && shouldPromote) {
      promotedPieceSquare = (Coordinate){secondSquare.row, secondSquare.col};
      if (isRedo)
        *movedPiece = data.undoData[data.nextUndoIndex + 1].newRank;
      else
        currentWindow = PROMOTION_WINDOW;
  }
}

_Bool isSkippedSquare (Coordinate square) {
  if (data.enPassantData.row == square.row && data.enPassantData.col == square.col) {
        return 1;
      } else {
        return 0;
      }
}

Coordinate getActualCoordinate(Coordinate originalCoordinate) {
  Coordinate actualCoordinate = {
    (data.player == 1 ? 7 - originalCoordinate.row : originalCoordinate.row),
    (data.player == 1 ? originalCoordinate.col : 7 - originalCoordinate.col)
  };
  return actualCoordinate;
}

Coordinate getDirection (int directionID) {
  Coordinate direction;
    if (directionID < 5) {
      direction.row = (directionID == 1 || directionID == 3) ? 1 : -1;
      direction.col = (directionID == 1 || directionID == 4) ? 1 : -1;
    } else if (directionID < 9) {
      direction.row = directionID == 5 ? 1 : directionID == 6 ? -1 : 0;
      direction.col = directionID == 7 ? 1 : directionID == 8 ? -1 : 0;
    } else if (directionID < 13) {
      direction.row = (directionID == 9 || directionID == 11) ? 1 : -1;
      direction.col = (directionID == 9 || directionID == 10) ? 2 : -2;
    } else if (directionID < 17) {
      direction.row = (directionID == 13 || directionID == 15) ? 2 : -2;
      direction.col = (directionID == 13 || directionID == 14) ? 1 : -1;
    }
    return direction;
}

_Bool isToBeChecked(Coordinate firstSquare, Coordinate secondSquare) {
  char testBoard[8][8];
  memcpy(testBoard, data.boardData, sizeof(char[8][8]));
  char *firstPiece = &testBoard[firstSquare.row][firstSquare.col];
  char *secondPiece = &testBoard[secondSquare.row][secondSquare.col];
  *secondPiece = *firstPiece;
  *firstPiece = DUMP_PIECE;
  return isPosChecked(data.kingPos[data.player - 1].row,
                      data.kingPos[data.player - 1].col, testBoard);
}

_Bool isAllowedMove (Coordinate newSquare) {
  int i;
  _Bool result = 0;
  for (i = 0;i < allowedSquaresNum;i++) {
    if (allowedSquares[i].row == newSquare.row && allowedSquares[i].col == newSquare.col) {
      result = 1;
      break;
    }
  }
  return result;
}

void appednAlgebraicNotation(_Bool isPromoted) {
  Step* lastUndoData = &data.undoData[data.undoDataSize - 1];
  char* algebraicData = lastUndoData->algebraicData;
  int colDiff = abs(lastUndoData->firstSquare.col - lastUndoData->secondSquare.col);
  int nextFill = 0;
  if (toupper(lastUndoData->firstPiece) == 'K' && colDiff > 1) {
    algebraicData[nextFill++] = 'O';
    algebraicData[nextFill++] = '-';
    algebraicData[nextFill++] = 'O';
    if (colDiff == 3) {
      algebraicData[nextFill++] = '-';
      algebraicData[nextFill++] = 'O';
    }
  } else {
    if (toupper(lastUndoData->firstPiece) != 'P')
      algebraicData[nextFill++] = toupper(lastUndoData->firstPiece);
    algebraicData[nextFill++] = lastUndoData->firstSquare.col + 97;
    algebraicData[nextFill++] = lastUndoData->firstSquare.row + 49;
    if (lastUndoData->capturedPlayer > 0)
      algebraicData[nextFill++] = 'x';
    algebraicData[nextFill++] = lastUndoData->secondSquare.col + 97;
    algebraicData[nextFill++] = lastUndoData->secondSquare.row + 49;
  }
  if (isPromoted) {
    lastUndoData->newRank = data.boardData[promotedPieceSquare.row][promotedPieceSquare.col];
    algebraicData[nextFill++] = '=';
    algebraicData[nextFill++] = toupper(lastUndoData->newRank);
  }
  if (data.playerState == CHECK)
    algebraicData[nextFill++] = '+';
  if (data.playerState == CHECKMATE)
    algebraicData[nextFill++] = '#';
  algebraicData[nextFill++] = '\0';
  updateLogTxt();
}

char* getAlgebraicLog() {
  int i;
  char* log = NULL;
  log = (char*)malloc(1);
  log[0] = '\0';
  int actualUndoDataSize = data.nextUndoIndex + 1;
  if (actualUndoDataSize > 0) {
    for (i = 0; i < actualUndoDataSize; i++) {
      if (i % 2 == 0) {
        char buffer[10];
        sprintf(buffer, "%d.", i / 2 + 1);
        log = (char*)realloc(log, strlen(buffer) + strlen(log) + 1);
        strcat(log, buffer);
      }
      log = (char*)realloc(log, strlen(data.undoData[i].algebraicData) + strlen(log) + 1);
      strcat(log, data.undoData[i].algebraicData);
      if (i < actualUndoDataSize - 1) {
        log = (char*)realloc(log, 1 + strlen(log) + 1);
        strcat(log, " ");
      }
    }
  }
  return log;
}

void fireDumpEvent() {
  SDL_Event dumpEvent;
  dumpEvent.type = SDL_MOUSEMOTION;
  SDL_PushEvent(&dumpEvent);
}

void goToMainMenu() {
    Mix_ChannelFinished(NULL);
    currentWindow = MAIN_MENU;
    fireDumpEvent();
    resetUndoData();
    resetLogTxt();
    resetSelection();
}

void endGameByCheckmate() {
    Mix_ChannelFinished(NULL);
    currentWindow = data.player == 1 ? PLAYER_TWO_VICTORY_WINDOW : PLAYER_ONE_VICTORY_WINDOW;
    fireDumpEvent();
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, victorySound, 0);
    Mix_ChannelFinished(goToMainMenu);
    savePGN();
}

void endGameByDraw() {
    Mix_ChannelFinished(NULL);
    currentWindow = DRAW_WINDOW;
    fireDumpEvent();
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, drawSound, 0);
    Mix_ChannelFinished(goToMainMenu);
    savePGN();
}

void playWarningSound() {
    Mix_ChannelFinished(NULL);
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, warningSound, 0);
}

void playSound (Mix_Chunk* sound) {
  Mix_ChannelFinished(NULL);
  Mix_HaltChannel(-1);
  Mix_PlayChannel(-1, sound, 0);
}

void getMissingFiles() {
  struct stat st = {0};
  char *absPath = SDL_GetBasePath();
  strcat(absPath, "saved");
  if (stat(absPath, &st) == -1) {
    mkdir(absPath);
  }
  strcat(absPath, "/pgn");
  if (stat(absPath, &st) == -1) {
    mkdir(absPath);
  }
}

void switchPlayer() { data.player = data.player == 1 ? 2 : 1; }

#endif