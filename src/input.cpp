#include "input.h"

Input::Input() {
    for (unsigned int i = 0; i < 65536; i++) {
        keys[i] = false;
    }
}

bool Input::keys[65536];
std::vector<SDL_Scancode> Input::pressed_keys;
std::vector<unsigned int> Input::clicked_buttons;
int Input::mx;
int Input::my;
int Input::mb;
bool Input::mg = false;

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
                if (!pressed_keys.empty() && std::find(pressed_keys.begin(), pressed_keys.end(), event.key.keysym.scancode) != pressed_keys.end()) {
                    pressed_keys.erase(std::find(pressed_keys.begin(), pressed_keys.end(), event.key.keysym.scancode));
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                mb = event.button.button;
                break;
            case SDL_MOUSEBUTTONUP:
                mb = 0;
                if (!clicked_buttons.empty() && std::find(clicked_buttons.begin(), clicked_buttons.end(), event.button.button) != clicked_buttons.end()) {
                    clicked_buttons.erase(std::find(clicked_buttons.begin(), clicked_buttons.end(), event.button.button));
                }
                break;
        }
    }
    SDL_GetMouseState(&mx, &my);
    
    if (key_pressed(SDL_SCANCODE_ESCAPE)) {
        mg = false;
        SDL_ShowCursor(SDL_ENABLE);
    }
    if (!mg && Input::get_mouse_button() == SDL_BUTTON_LEFT) {
        mg = true;
        SDL_ShowCursor(SDL_DISABLE);
    }
}

bool Input::key_pressed(SDL_Scancode key) {
    return keys[key];
}

bool Input::key_typed(SDL_Scancode key) {
    bool pressed = key_pressed(key);
    if (!pressed) return false;
    if(!pressed_keys.empty() && std::find(pressed_keys.begin(), pressed_keys.end(), key) != pressed_keys.end()) {
        return false;
    }
    pressed_keys.push_back(key);
    return true;
}

bool Input::mouse_clicked(unsigned int button) {
    bool clicked = mb == button;
    if (!clicked) return false;
    if(!clicked_buttons.empty() && std::find(clicked_buttons.begin(), clicked_buttons.end(), button) != clicked_buttons.end()) {
        return false;
    }
    clicked_buttons.push_back(button);
    return true;}

int Input::get_mouse_button() {
    return mb;
}

bool Input::mouse_grabbed() {
    return mg;
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