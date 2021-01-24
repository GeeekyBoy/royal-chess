#ifndef UNDO_H
#define UNDO_H

#include "definitions.h"

void addUndoData(char firstPiece, Coordinate firstSquare,
                 char secondPiece, Coordinate secondSquare,
                 int capturedPlayer) {
  data.undoData =
      realloc(data.undoData, (data.nextUndoIndex + 2) * sizeof(Step));
  data.undoData[data.nextUndoIndex + 1].firstPiece = firstPiece;
  data.undoData[data.nextUndoIndex + 1].firstSquare = firstSquare;
  data.undoData[data.nextUndoIndex + 1].secondPiece = secondPiece;
  data.undoData[data.nextUndoIndex + 1].secondSquare = secondSquare;
  data.undoData[data.nextUndoIndex + 1].capturedPlayer = capturedPlayer;
	memmove(data.undoData[data.nextUndoIndex + 1].castlingData, data.castlingData, sizeof(_Bool[2][3]));
  data.undoData[data.nextUndoIndex + 1].enPassantData = data.enPassantData;
  data.undoData[data.nextUndoIndex + 1].playerState = data.playerState;
  data.undoDataSize = data.nextUndoIndex + 2;
  data.nextUndoIndex++;
}

void undo() {
  Mix_ChannelFinished(NULL);
  Mix_HaltChannel(-1);
  if (data.nextUndoIndex > -1) {
    int index = data.nextUndoIndex;
    char firstPiece = data.undoData[index].firstPiece;
    Coordinate firstSquare = data.undoData[index].firstSquare;
    char secondPiece = data.undoData[index].secondPiece;
    Coordinate secondSquare = data.undoData[index].secondSquare;
    int capturedPlayer = data.undoData[index].capturedPlayer;
    int playerState = data.undoData[index].playerState;
    data.boardData[firstSquare.row][firstSquare.col] = firstPiece;
    data.boardData[secondSquare.row][secondSquare.col] = secondPiece;
    memmove(data.castlingData, data.undoData[index].castlingData, sizeof(_Bool[2][3]));
    data.enPassantData = data.undoData[index].enPassantData;
    updateKingPos(firstPiece, firstSquare);
    if (capturedPlayer > 0)
      data.capturedNum[capturedPlayer - 1]--;
    switchPlayer();
    data.playerState = playerState;
    resetSelection();
    doCastling(firstSquare, secondSquare, 1);
    doEnpassant(firstSquare, secondSquare, 1);
    data.nextUndoIndex--;
    Mix_PlayChannel(-1, undoSound, 0);
    updateLogTxt();
  } else {
    Mix_PlayChannel(-1, errorSound, 0);
  }
}

void redo() {
  Mix_ChannelFinished(NULL);
  Mix_HaltChannel(-1);
  if (data.nextUndoIndex < data.undoDataSize - 1) {
    int index = data.nextUndoIndex + 1;
    Coordinate firstSquare = data.undoData[index].firstSquare;
    Coordinate secondSquare = data.undoData[index].secondSquare;
    char* firstPiece = &data.boardData[firstSquare.row][firstSquare.col];
    char* secondPiece = &data.boardData[secondSquare.row][secondSquare.col];
    capture(*secondPiece);
    updateKingPos(*firstPiece, secondSquare);
    doPromotion(firstSquare, secondSquare, 1);
    doCastling(firstSquare, secondSquare, 0);
    doEnpassant(firstSquare, secondSquare, 0);
    setCastlingState(firstSquare);
    setEnPassantData(firstSquare, secondSquare);
    *secondPiece = *firstPiece;
    *firstPiece = DUMP_PIECE;
    switchPlayer();
    setPlayerState();
    resetSelection();
    data.nextUndoIndex++;
    Mix_PlayChannel(-1, redoSound, 0);
    updateLogTxt();
  } else {
    Mix_PlayChannel(-1, errorSound, 0);
  }
}

#endif