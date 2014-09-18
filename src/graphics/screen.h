#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

#include "shader.h"
#include "texture.h"
#include "../input.h"

class Screen {
private:
    const char *title;
    int width, height;
    SDL_Window *window;
    bool mouse_grabbed = true;
public:
    Screen(const char *title, int width, int height);
    ~Screen();
    void clear();
    void update();
    int get_width();
    int get_height();
private:
    void initGL();
};
