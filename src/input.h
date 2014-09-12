#pragma once

#include <iostream>
#include <vector>
#include <SDL2/SDl.h>

class Input {
private:
    SDL_Event event;
    static bool keys[65536];
    bool quit = false;
    static int mx, my;
public:
    Input();
    void update();
    std::vector<SDL_Keycode> get_pressed_keys();
    static bool key_pressed(SDL_Scancode key);
    static int get_DX();
    static int get_DY();
    bool window_closed();
};