#include "input.h"

Input::Input() {
    for (unsigned int i = 0; i < 65536; i++) {
        keys[i] = false;
    }
}

bool Input::keys[65536];
int Input::mx;
int Input::my;

void Input::update() {
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_KEYDOWN:
                keys[event.key.keysym.scancode] = true;
                break;
            case SDL_KEYUP:
                keys[event.key.keysym.scancode] = false;
                break;
        }
    }
    SDL_GetMouseState(&mx, &my);
}

bool Input::key_pressed(SDL_Scancode key) {
    return keys[key];
}

std::vector<int> Input::get_pressed_keys() {
    std::vector<int> result;
    for (unsigned int i = 0; i < 65536; i++) {
        if (keys[i]) result.push_back(i);
    }
    return result;
}

int Input::get_DX() {
    return 1280 / 2 - mx;
}

int Input::get_DY() {
    return 720 / 2 - my;
}

bool Input::window_closed() {
    return quit;
}