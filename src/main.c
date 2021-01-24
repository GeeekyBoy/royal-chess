#include "definitions.h"

#include "core.h"
#include "eventshandler.h"
#include "lifecycle.h"
#include "loadres.h"
#include "render.h"
#include "reset.h"
#include "save.h"
#include "undo.h"
#include "utils.h"

int wmain(int argc, char *argv[]) {
      const SDL_MessageBoxButtonData buttons[] = {
        { SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "640x480" },
        { 0, 2, "1280x960" },
        { 0, 3, "2560x1920" },
    };
    const SDL_MessageBoxData messageboxdata = {
        SDL_MESSAGEBOX_INFORMATION,
        NULL,
        "Game Resolution",
        "Select the best resolution that fits your monitor",
        SDL_arraysize(buttons),
        buttons,
        NULL
    };
    int buttonid;
    if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
        SDL_Log("error displaying message box");
        return 1;
    } else {
      screenScale = buttonid;
      Game.screen.w = screenScale * SCREEN_W;
      Game.screen.h = screenScale * SCREEN_H;
    }
  Game.init();
  SDL_Event event;
  while (Game.running) {
    if (SDL_WaitEvent(&event) != 0) {
      int x, y;
      switch (event.type) {
      case SDL_QUIT:
        Game.running = SDL_FALSE;
        break;
      case SDL_MOUSEBUTTONDOWN:
        SDL_GetMouseState(&x, &y);
        handleMouseEvent(x, y, event.button.button, event.type);
        break;
      case SDL_MOUSEMOTION:
        SDL_GetMouseState(&x, &y);
        handleMouseEvent(x, y, event.button.button, event.type);
        break;
      case SDL_MOUSEWHEEL:
        SDL_GetMouseState(&x, &y);
        handleMousewheelEvent(x, y, event.wheel.y);
        break;
      }
    }
    renderFrame();
  }
  Game.quit();
  return 0;
}