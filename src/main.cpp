#include <iostream>
#include <SDL2/SDL_timer.h>

#include "game.h"

int main(int argc, const char * argv[]) {
    Game game("ChernoCraft", 1280, 720);
    long last_time = SDL_GetTicks();
    double delta = 0.0;
    int updates = 0;
    int frames = 0;
    long timer = SDL_GetTicks();
    
    while (game.is_running()) {
        long now = SDL_GetTicks();
        delta += (now - last_time) / (1000.0 / 60.0);
        last_time = now;
        if (delta >= 1.0) {
            game.update();
            updates++;
            delta--;
        }
        game.render();
        frames++;
        if (SDL_GetTicks() - timer > 1000) {
            timer += 1000;
            std::cout << updates << " ups, " << frames << " fps" << std::endl;
            updates = 0;
            frames = 0;
        }
    }
    
    return 0;
}
