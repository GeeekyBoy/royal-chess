#ifndef CORE_H
#define CORE_H

#include "definitions.h"

static void setPlayerState();
static _Bool isDeadPos();
static _Bool isPosChecked(int row, int col, char board[8][8]);

static _Bool isPosChecked(int row, int col, char board[8][8]) {
  int searchDir;
  _Bool isChecked = 0;
  for (searchDir = 1; searchDir < 17; searchDir++) {
    Coordinate increment = getDirection(searchDir);
    int currRow = row + increment.row;
    int currCol = col + increment.col;
    char currSquare = board[currRow][currCol];
    if (searchDir < 9) {
      _Bool isfirstStep = 1;
      while (isInBounds(currRow, currCol)) {
        currSquare = board[currRow][currCol];
            if (isfirstStep &&
                currSquare == getRightPiece('p', 0) &&
                ((data.player == 1 && (searchDir == 1 || searchDir == 3)) ||
                (data.player == 2 && (searchDir == 2 || searchDir == 4)))) {
                isChecked = 1;
                break;
            } else if ((currSquare == getRightPiece('q', 0)) ||
                       (isfirstStep && currSquare == getRightPiece('k', 0)) ||
                       (searchDir < 5 && currSquare == getRightPiece('b', 0)) ||
                       (searchDir > 4 && searchDir < 9 &&
                        currSquare == getRightPiece('r', 0))) {
              isChecked = 1;
              break;
            } else if (currSquare != DUMP_PIECE) {
              break;
            }
          isfirstStep = 0;
          currRow += increment.row;
          currCol += increment.col;
      }
    } else if (isInBounds(currRow, currCol) &&
               board[currRow][currCol] == getRightPiece('n', 0)) {
      isChecked = 1;
      break;
    }
    if (isChecked) {
      break;
    }
  }
  return isChecked;
}

_Bool isMovable(Coordinate coordinate, _Bool isInternal) {
  _Bool result = 0;
  int searchDir;
  char originSquare = data.boardData[coordinate.row][coordinate.col];
  for (searchDir = 1; searchDir < 17; searchDir++) {
    Coordinate increment = getDirection(searchDir);
    int currRow = coordinate.row + increment.row;
    int currCol = coordinate.col + increment.col;
    int stepsCount = 1;
    char currSquare = data.boardData[currRow][currCol];
    if (searchDir < 9) {
      while (isInBounds(currRow, currCol)) {
        currSquare = data.boardData[currRow][currCol];
        if ((stepsCount == 1 && originSquare == getRightPiece('p', 1) &&
             ((((currSquare != DUMP_PIECE && !isOwned(currSquare)) ||
                (currSquare == DUMP_PIECE &&
                 isSkippedSquare((Coordinate){currRow, currCol}))) &&
               (searchDir == data.player || searchDir == data.player + 2)) ||
              (currSquare == DUMP_PIECE && searchDir == data.player + 4)))) {
          if (!isToBeChecked(coordinate, (Coordinate){currRow, currCol})) {
            if (!isInternal) {
              allowedSquares[allowedSquaresNum++] =
                  (Coordinate){currRow, currCol};
            }
            if (isFirstPawnMove(coordinate.row) &&
                data.boardData[currRow + increment.row][currCol + increment.col] == DUMP_PIECE &&
                (searchDir == data.player + 4)) {
              if (!isInternal) {
                allowedSquares[allowedSquaresNum++] = (Coordinate){
                    currRow + increment.row, currCol + increment.col};
              }
            }
            result = 1;
          }
          break;
        } else if ((originSquare == getRightPiece('q', 1)) ||
                   (searchDir < 5 && originSquare == getRightPiece('b', 1)) ||
                   (searchDir > 4 && searchDir < 9 &&
                    originSquare == getRightPiece('r', 1))) {
          if (currSquare == DUMP_PIECE || !isOwned(currSquare)) {
            if (!isToBeChecked(coordinate, (Coordinate){currRow, currCol})) {
              if (!isInternal) {
                allowedSquares[allowedSquaresNum++] =
                    (Coordinate){currRow, currCol};
              }
              result = 1;
            }
          }
          if (currSquare != DUMP_PIECE) {
            break;
          }
        } else if (originSquare == getRightPiece('k', 1) &&
                   !isPosChecked(currRow, currCol, data.boardData)) {
          if (stepsCount == 1) {
            if (currSquare == DUMP_PIECE || !isOwned(currSquare)) {
              if (!isInternal) {
                allowedSquares[allowedSquaresNum++] =
                    (Coordinate){currRow, currCol};
              }
              result = 1;
            }
            if ((searchDir != 7 && searchDir != 8) || currSquare != DUMP_PIECE) {
              break;
            }
          } else if (data.castlingData[data.player - 1][1] == 1 &&
                     currSquare == DUMP_PIECE) {
            if ((stepsCount == 2 && searchDir == 7 &&
                 data.castlingData[data.player - 1][2] == 1) ||
                (stepsCount == 3 && searchDir == 8 &&
                 data.castlingData[data.player - 1][0] == 1)) {
              if (!isInternal) {
                allowedSquares[allowedSquaresNum++] =
                    (Coordinate){currRow, currCol};
              }
              result = 1;
              break;
            }
          } else if (currSquare != DUMP_PIECE) {
            break;
          }
        }
        stepsCount++;
        currRow += increment.row;
        currCol += increment.col;
      }
    } else if (originSquare == getRightPiece('n', 1) &&
          isInBounds(currRow, currCol)) {
        if (currSquare == DUMP_PIECE || !isOwned(currSquare)) {
          if (!isToBeChecked(coordinate, (Coordinate){currRow, currCol})) {
            if (!isInternal) {
              allowedSquares[allowedSquaresNum++] = (Coordinate){currRow, currCol};
            }
            result = 1;
          }
        }
      }
  }
  return result;
}

int capture(char replacedPiece) {
  int capturedPlayer = 0;
  if (replacedPiece != DUMP_PIECE) {
    capturedPlayer = data.player == 1 ? 2 : 1;
    data.capturedPieces[capturedPlayer - 1][data.capturedNum[capturedPlayer - 1]++] = replacedPiece;
  } 
  return capturedPlayer;
}

static _Bool isDeadPos() {
  int darkBishops = 0, lightBishops = 0, knights = 0, pieces = 0;
  int row, col;
  for (row = 7; row >= 0; row--) {
    for (col = 0; col < 8; col++) {
      char currSquare = data.boardData[row][col];
      _Bool isDark = ((row + 1) + (col + 1)) % 2 == 0;
      if (toupper(currSquare) == 'Q' || toupper(currSquare) == 'R' ||
          toupper(currSquare) == 'B' || toupper(currSquare) == 'P' ||
          toupper(currSquare) == 'N') {
        pieces++;
        if (toupper(currSquare) == 'B') {
          if (isDark) {
            darkBishops++;
          } else {
            lightBishops++;
          }
        } else if (toupper(currSquare) == 'N') {
          knights++;
        }
      }
    }
  }
  if ((pieces == 2 && (darkBishops == 2 || lightBishops == 2)) ||
      (pieces == 1 &&
       (lightBishops == 1 || darkBishops == 1 || knights == 1)) ||
      (pieces == 0)) {
    return 1;
  } else {
    return 0;
  }
}

static void setPlayerState() {
  if (isDeadPos()) {
    data.playerState = DEAD_POSITION;
    return;
  }
  _Bool isKingChecked =
      isPosChecked(data.kingPos[data.player - 1].row,
                   data.kingPos[data.player - 1].col, data.boardData);
  if (!isMovable(data.kingPos[data.player - 1], 1)) {
    int row, col;
    for (row = 7; row >= 0; row--) {
      for (col = 0; col < 8; col++) {
        char currSquare = data.boardData[row][col];
        if (currSquare == getRightPiece('q', 1) ||
            currSquare == getRightPiece('r', 1) ||
            currSquare == getRightPiece('b', 1) ||
            currSquare == getRightPiece('p', 1) ||
            currSquare == getRightPiece('n', 1)) {
          if (isMovable((Coordinate){row, col}, 1)) {
            if (isKingChecked) {
              data.playerState = CHECK;
            } else {
              data.playerState = NONE;
            }
            return;
          }
        }
      }
    }
    if (!isKingChecked) {
      data.playerState = STALEMATE;
    } else {
      data.playerState = CHECKMATE;
    }
  } else if (isKingChecked) {
    data.playerState = CHECK;
  } else {
    data.playerState = NONE;
  }
}

void askForMove(Coordinate firstSquare, Coordinate secondSquare) {
  char* firstPiece = &data.boardData[firstSquare.row][firstSquare.col];
  char* secondPiece = &data.boardData[secondSquare.row][secondSquare.col];
  int capturedPlayer = capture(*secondPiece);
  updateKingPos(*firstPiece, secondSquare);
  addUndoData(*firstPiece, firstSquare, *secondPiece, secondSquare, capturedPlayer);
  doPromotion(firstSquare, secondSquare, 0);
  doCastling(firstSquare, secondSquare, 0);
  doEnpassant(firstSquare, secondSquare, 0);
  setCastlingState(firstSquare);
  setEnPassantData(firstSquare, secondSquare);
  *secondPiece = *firstPiece;
  *firstPiece = DUMP_PIECE;
  switchPlayer();
  setPlayerState();
  resetSelection();
  playSound(moveSound);
  applyPlayerState();
  appednAlgebraicNotation(0);
}

#endif