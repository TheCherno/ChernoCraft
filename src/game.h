#pragma once

#include "graphics/screen.h"
#include "input.h"
#include "level/level.h"
#include "utils/fileutils.h"

class Game {
private:
    Screen screen;
    bool running = false;
    Input input;
    Level *level;
public:
    Game(const char *title, int width, int height);
    bool is_running();
    void update();
    void render();
};
