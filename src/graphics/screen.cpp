#include "screen.h"

Screen::Screen(const char *title, int width, int height) {
    this->title = title;
    this->width = width;
    this->height = height;
    
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        throw new std::runtime_error("Could not create SDL window!");
    }
    initGL();
}

Screen::~Screen() {
    SDL_DestroyWindow(window);
}

void Screen::initGL() {
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_CreateContext(window);
    SDL_ShowCursor(SDL_DISABLE);
    
    std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;
    
    glEnable(GL_DEPTH_TEST);
   // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    Shader::LOAD();
}

void Screen::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Screen::update() {
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << error << std::endl;
    }
    SDL_WarpMouseInWindow(window, width / 2, height / 2);
    SDL_GL_SwapWindow(window);
}

int Screen::get_width() {
    return width;
}

int Screen::get_height() {
    return height;
}