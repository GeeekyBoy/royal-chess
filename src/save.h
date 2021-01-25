#ifndef SAVE_H 
#define SAVE_H

#include "definitions.h"

void saveGame() {
  getMissingFiles();
  FILE *gamedataFile;
  size_t firstSize = sizeof(Gamedata);
  size_t secondSize = data.undoDataSize * sizeof(Step);
  char *absPath = SDL_GetBasePath();
  strcat(absPath, "saved/lastGame.royalChess");
  gamedataFile = fopen(absPath, "wb");
  fwrite(&data, firstSize, 1, gamedataFile);
  fflush(gamedataFile);
  fwrite(data.undoData, secondSize, 1, gamedataFile);
  fflush(gamedataFile);
  fclose(gamedataFile);
}

void savePGN() {
  getMissingFiles();
  time_t rawTime = time(NULL);
  struct tm *parsedTime = localtime(&rawTime);
  char formattedTime[25];
  strftime(formattedTime, sizeof(formattedTime), "%d-%m-%Y-%I-%M-%S%p", parsedTime);
  FILE *pgnFile;
  char *absPath = SDL_GetBasePath();
  strcat(absPath, "saved/pgn/");
  strcat(absPath, formattedTime);
  strcat(absPath, ".pgn");
  pgnFile = fopen(absPath, "wb");
  fprintf(pgnFile, "[Event \"Royal Chess\"]\n");
  fprintf(pgnFile, "[Site \"Personal Computer\"]\n");
  strftime(formattedTime, sizeof(formattedTime), "%Y.%m.%d", parsedTime);
  fprintf(pgnFile, "[Date \"%s\"]\n", formattedTime);
  fprintf(pgnFile, "[Round \"1\"]\n");
  fprintf(pgnFile, "[White \"Player 1\"]\n");
  fprintf(pgnFile, "[Black \"Player 2\"]\n");
  fprintf(pgnFile, "[PlyCount \"%d\"]\n", data.undoDataSize);
  if (currentWindow == PLAYER_ONE_VICTORY_WINDOW)
    fprintf(pgnFile, "[Result \"1-0\"]\n\n");
  else if (currentWindow == PLAYER_TWO_VICTORY_WINDOW)
    fprintf(pgnFile, "[Result \"0-1\"]\n\n");
  else if (currentWindow == DRAW_WINDOW)
    fprintf(pgnFile, "[Result \"1/2-1/2\"]\n\n");
  fprintf(pgnFile, getAlgebraicLog());
  fflush(pgnFile);
  fclose(pgnFile);
}

void loadGame() {
  getMissingFiles();
  FILE *gamedataFile;
  size_t firstSize = sizeof(Gamedata);
  char *absPath = SDL_GetBasePath();
  strcat(absPath, "saved/lastGame.royalChess");
  struct stat st = {0};
  if (stat(absPath, &st) == -1) {
    newGame();
  } else {
    gamedataFile = fopen(absPath, "rb");
    fread(&data, firstSize, 1, gamedataFile);
    size_t secondSize = data.undoDataSize * sizeof(Step);
    data.undoData = malloc(secondSize);
    fread(data.undoData, secondSize, 1, gamedataFile);
    fclose(gamedataFile);
    updateLogTxt();
  }
}

#endif