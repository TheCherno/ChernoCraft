#include "game.h"

Game::Game(const char *title, int width, int height) :
    screen(Screen(title, width, height)) {
        
}

bool Game::is_running() {
    return !input.window_closed();
}

void Game::update() {
    input.update();
}

void Game::render() {
    screen.clear();
    screen.update();
}

