/**
 * @file loadres.h
 * @author GeeekyBoy
 * @brief Loading of all game resources including audio and fonts.
 * \copyright Copyright 2021 GeeekyBoy Studio. All rights reserved.
    This project is released under the GNU Affero General Public License v3.
 */

#ifndef LOADRES_H
#define LOADRES_H

#include "definitions.h"

#define INCBIN_PREFIX RAW_
#include "lib/incbin/incbin.h"
INCBIN(gameBackgroundTile, __ASSETS__ "bg.svg");
INCBIN(drawDialog, __ASSETS__ "dialogs/draw.svg");
INCBIN(mainMenuDialog, __ASSETS__ "dialogs/mainMenu.svg");
INCBIN(playerOneVictoryDialog, __ASSETS__ "dialogs/playerOneVictory.svg");
INCBIN(playerTwoVictoryDialog, __ASSETS__ "dialogs/playerTwoVictory.svg");
INCBIN(saveGameDialog, __ASSETS__ "dialogs/saveGame.svg");
INCBIN(drawAgreementDialog, __ASSETS__ "dialogs/drawAgreement.svg");
INCBIN(saveConfirmedDialog, __ASSETS__ "dialogs/saveConfirmed.svg");
INCBIN(promotionDialog, __ASSETS__ "dialogs/promotion.svg");
INCBIN(endGameDialog, __ASSETS__ "dialogs/endGame.svg");
INCBIN(saveGameBtn, __ASSETS__ "buttons/saveGame.svg");
INCBIN(endGameBtn, __ASSETS__ "buttons/endGame.svg");
INCBIN(undoBtn, __ASSETS__ "buttons/undo.svg");
INCBIN(windowedBtn, __ASSETS__ "buttons/windowed.svg");
INCBIN(fullscreenBtn, __ASSETS__ "buttons/fullscreen.svg");
INCBIN(board, __ASSETS__ "board.svg");
INCBIN(playerOneCaptured, __ASSETS__ "playerOneCaptured.svg");
INCBIN(playerTwoCaptured, __ASSETS__ "playerTwoCaptured.svg");
INCBIN(selectedTile, __ASSETS__ "selected.svg");
INCBIN(allowedTile, __ASSETS__ "allowed.svg");
INCBIN(logTile, __ASSETS__ "logTile.svg");
INCBIN(playerOneTile, __ASSETS__ "playerOneTile.svg");
INCBIN(playerTwoTile, __ASSETS__ "playerTwoTile.svg");
INCBIN(darkTile, __ASSETS__ "dark.svg");
INCBIN(lightTile, __ASSETS__ "light.svg");
INCBIN(kingTile, __ASSETS__ "pieces/k.svg");
INCBIN(rookTile, __ASSETS__ "pieces/r.svg");
INCBIN(queenTile, __ASSETS__ "pieces/q.svg");
INCBIN(bishopTile, __ASSETS__ "pieces/b.svg");
INCBIN(knightTile, __ASSETS__ "pieces/n.svg");
INCBIN(pawnTile, __ASSETS__ "pieces/p.svg");
INCBIN(kingDarkTile, __ASSETS__ "pieces/kd.svg");
INCBIN(rookDarkTile, __ASSETS__ "pieces/rd.svg");
INCBIN(queenDarkTile, __ASSETS__ "pieces/qd.svg");
INCBIN(bishopDarkTile, __ASSETS__ "pieces/bd.svg");
INCBIN(knightDarkTile, __ASSETS__ "pieces/nd.svg");
INCBIN(pawnDarkTile, __ASSETS__ "pieces/pd.svg");
INCBIN(kingSmallTile, __ASSETS__ "pieces/small/k.svg");
INCBIN(rookSmallTile, __ASSETS__ "pieces/small/q.svg");
INCBIN(queenSmallTile, __ASSETS__ "pieces/small/q.svg");
INCBIN(bishopSmallTile, __ASSETS__ "pieces/small/b.svg");
INCBIN(knightSmallTile, __ASSETS__ "pieces/small/n.svg");
INCBIN(pawnSmallTile, __ASSETS__ "pieces/small/p.svg");
INCBIN(kingDarkSmallTile, __ASSETS__ "pieces/small/kd.svg");
INCBIN(rookDarkSmallTile, __ASSETS__ "pieces/small/rd.svg");
INCBIN(queenDarkSmallTile, __ASSETS__ "pieces/small/qd.svg");
INCBIN(bishopDarkSmallTile, __ASSETS__ "pieces/small/bd.svg");
INCBIN(knightDarkSmallTile, __ASSETS__ "pieces/small/nd.svg");
INCBIN(pawnDarkSmallTile, __ASSETS__ "pieces/small/pd.svg");
INCBIN(moveSound, __ASSETS__ "audio/move.wav");
INCBIN(checkSound, __ASSETS__ "audio/check.wav");
INCBIN(checkmateSound, __ASSETS__ "audio/checkmate.wav");
INCBIN(stalemateSound, __ASSETS__ "audio/stalemate.wav");
INCBIN(victorySound, __ASSETS__ "audio/victory.wav");
INCBIN(drawSound, __ASSETS__ "audio/draw.wav");
INCBIN(warningSound, __ASSETS__ "audio/warning.wav");
INCBIN(deadPositionSound, __ASSETS__ "audio/deadPosition.wav");
INCBIN(promotionSound, __ASSETS__ "audio/promotion.wav");
INCBIN(undoSound, __ASSETS__ "audio/undo.wav");
INCBIN(redoSound, __ASSETS__ "audio/redo.wav");
INCBIN(errorSound, __ASSETS__ "audio/error.wav");
INCBIN(clickSound, __ASSETS__ "audio/click.wav");
INCBIN(startGameSound, __ASSETS__ "audio/startGame.wav");
INCBIN(arrowCursor, __ASSETS__ "cursors/arrow.svg");
INCBIN(handCursor, __ASSETS__ "cursors/hand.svg");
INCBIN(robotoFont, __ASSETS__ "fonts/Roboto-Bold.ttf");

/**
 *  \brief Convert SVG data of the cursor into real cursor
 *
 *  \param svgData Data of the included SVG resource
 *  \return Data of the actual cursor
 *
 *  \sa svg2cursor
 */
static SDL_Cursor *svg2cursor (char *svgData);

Image svg2tex (char *svgData) {
    Image result;
    NSVGimage *image = NULL;
    NSVGrasterizer *rast = NULL;
    unsigned char *img = NULL;
    image = nsvgParse(svgData, "px", 96.0f);
    result.width = ((int)image->width) * screenScale;
    result.height = ((int)image->height) * screenScale;
    rast = nsvgCreateRasterizer();
    img = malloc(result.width*result.height*4);
    nsvgRasterize(rast, image, 0,0,screenScale, img, result.width, result.height, result.width*4);
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(img, result.width, result.height, 32, result.width*4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    result.tex = SDL_CreateTextureFromSurface(Game.screen.renderer, surface);
    free(img);
    SDL_FreeSurface(surface);
    return result;
}

static SDL_Cursor *svg2cursor (char *svgData) {
    SDL_Cursor *cursor = NULL;
    NSVGimage *image = NULL;
    NSVGrasterizer *rast = NULL;
    unsigned char *img = NULL;
    image = nsvgParse(svgData, "px", 96.0f);
    int width = ((int)image->width) * screenScale;
    int height = ((int)image->height) * screenScale;
    rast = nsvgCreateRasterizer();
    img = malloc(width*height*4);
    nsvgRasterize(rast, image, 0,0,screenScale, img, width, height, width*4);
    nsvgDeleteRasterizer(rast);
    nsvgDelete(image);
    SDL_Surface *surface = SDL_CreateRGBSurfaceFrom(img, width, height, 32, width*4, 0x000000FF, 0x0000FF00, 0x00FF0000, 0xFF000000);
    cursor = SDL_CreateColorCursor(surface, 0, 0);
    free(img);
    SDL_FreeSurface(surface);
    return cursor;
}

int loadRes(void* data) {
    gameBackgroundTile = svg2tex((char*)RAW_gameBackgroundTileData);
    mainMenuDialog = svg2tex((char*)RAW_mainMenuDialogData);
    drawDialog = svg2tex((char*)RAW_drawDialogData);
    playerOneVictoryDialog = svg2tex((char*)RAW_playerOneVictoryDialogData);
    playerTwoVictoryDialog = svg2tex((char*)RAW_playerTwoVictoryDialogData);
    drawAgreementDialog = svg2tex((char*)RAW_drawAgreementDialogData);
    saveGameDialog = svg2tex((char*)RAW_saveGameDialogData);
    saveConfirmedDialog = svg2tex((char*)RAW_saveConfirmedDialogData);
    promotionDialog = svg2tex((char*)RAW_promotionDialogData);
    endGameDialog = svg2tex((char*)RAW_endGameDialogData);
    saveGameBtn = svg2tex((char*)RAW_saveGameBtnData);
    endGameBtn = svg2tex((char*)RAW_endGameBtnData);
    undoBtn = svg2tex((char*)RAW_undoBtnData);
    windowedBtn = svg2tex((char*)RAW_windowedBtnData);
    fullscreenBtn = svg2tex((char*)RAW_fullscreenBtnData);
    board = svg2tex((char*)RAW_boardData);
    playerOneCaptured = svg2tex((char*)RAW_playerOneCapturedData);
    playerTwoCaptured = svg2tex((char*)RAW_playerTwoCapturedData);
    selectedTile = svg2tex((char*)RAW_selectedTileData);
    allowedTile = svg2tex((char*)RAW_allowedTileData);
    logTile = svg2tex((char*)RAW_logTileData);
    playerOneTile = svg2tex((char*)RAW_playerOneTileData);
    playerTwoTile = svg2tex((char*)RAW_playerTwoTileData);
    darkTile = svg2tex((char*)RAW_darkTileData);
    lightTile = svg2tex((char*)RAW_lightTileData);
    kingTile = svg2tex((char*)RAW_kingTileData);
    rookTile = svg2tex((char*)RAW_rookTileData);
    queenTile = svg2tex((char*)RAW_queenTileData);
    bishopTile = svg2tex((char*)RAW_bishopTileData);
    knightTile = svg2tex((char*)RAW_knightTileData);
    pawnTile = svg2tex((char*)RAW_pawnTileData);
    kingDarkTile = svg2tex((char*)RAW_kingDarkTileData);
    rookDarkTile = svg2tex((char*)RAW_rookDarkTileData);
    queenDarkTile = svg2tex((char*)RAW_queenDarkTileData);
    bishopDarkTile = svg2tex((char*)RAW_bishopDarkTileData);
    knightDarkTile = svg2tex((char*)RAW_knightDarkTileData);
    pawnDarkTile = svg2tex((char*)RAW_pawnDarkTileData);
    kingSmallTile = svg2tex((char*)RAW_kingSmallTileData);
    rookSmallTile = svg2tex((char*)RAW_rookSmallTileData);
    queenSmallTile = svg2tex((char*)RAW_queenSmallTileData);
    bishopSmallTile = svg2tex((char*)RAW_bishopSmallTileData);
    knightSmallTile = svg2tex((char*)RAW_knightSmallTileData);
    pawnSmallTile = svg2tex((char*)RAW_pawnSmallTileData);
    kingDarkSmallTile = svg2tex((char*)RAW_kingDarkSmallTileData);
    rookDarkSmallTile = svg2tex((char*)RAW_rookDarkSmallTileData);
    queenDarkSmallTile = svg2tex((char*)RAW_queenDarkSmallTileData);
    bishopDarkSmallTile = svg2tex((char*)RAW_bishopDarkSmallTileData);
    knightDarkSmallTile = svg2tex((char*)RAW_knightDarkSmallTileData);
    pawnDarkSmallTile = svg2tex((char*)RAW_pawnDarkSmallTileData);
    moveSound = Mix_QuickLoad_WAV((Uint8*)RAW_moveSoundData);
	checkSound = Mix_QuickLoad_WAV((Uint8*)RAW_checkSoundData);
	checkmateSound = Mix_QuickLoad_WAV((Uint8*)RAW_checkmateSoundData);
	stalemateSound = Mix_QuickLoad_WAV((Uint8*)RAW_stalemateSoundData);
	victorySound = Mix_QuickLoad_WAV((Uint8*)RAW_victorySoundData);
	drawSound = Mix_QuickLoad_WAV((Uint8*)RAW_drawSoundData);
	warningSound = Mix_QuickLoad_WAV((Uint8*)RAW_warningSoundData);
	deadPositionSound = Mix_QuickLoad_WAV((Uint8*)RAW_deadPositionSoundData);
	promotionSound = Mix_QuickLoad_WAV((Uint8*)RAW_promotionSoundData);
	undoSound = Mix_QuickLoad_WAV((Uint8*)RAW_undoSoundData);
	redoSound = Mix_QuickLoad_WAV((Uint8*)RAW_redoSoundData);
	errorSound = Mix_QuickLoad_WAV((Uint8*)RAW_errorSoundData);
	clickSound = Mix_QuickLoad_WAV((Uint8*)RAW_clickSoundData);
	startGameSound = Mix_QuickLoad_WAV((Uint8*)RAW_startGameSoundData);
    arrowCursor = svg2cursor((char*)RAW_arrowCursorData);
    handCursor = svg2cursor((char*)RAW_handCursorData);
    robotoBold = TTF_OpenFontRW(SDL_RWFromConstMem(RAW_robotoFontData, RAW_robotoFontSize), 1, 10 * screenScale);
    noCapturedTxt = mkTxt("You have captured nothing !", robotoBold, brownTxtColor, 160);
    texInitState = 2;
    SDL_SetCursor(arrowCursor);
    SDL_ShowCursor(SDL_ENABLE);
    fireDumpEvent();
    return 0;
}

#endif