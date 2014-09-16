#include "game.h"

Game::Game(const char *title, int width, int height) :
    screen(Screen(title, width, height)) {
    level = new Level();
}

Game::~Game() {
    delete level;
}

bool Game::is_running() {
    return !input.window_closed();
}

void Game::update() {
    input.update();
    level->update();
}

void Game::render() {
    screen.clear();
    level->render();
    screen.update();
}