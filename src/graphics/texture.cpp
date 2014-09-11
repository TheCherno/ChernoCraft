#include "texture.h"

Texture::Texture(std::string file) {
    texture = load(file);
}

void Texture::LOAD() {
    // Load static textures here
}

GLuint Texture::load(std::string filepath) {
    SDL_Surface *texture = IMG_Load(filepath.c_str());
    GLuint *pixels = (GLuint*) texture->pixels;
    
    for (int i = 0; i < texture->w * texture->h; i++) {
        GLuint a = (pixels[i] & 0xff000000) >> 24;
        GLuint r = (pixels[i] & 0xff0000) >> 16;
        GLuint g = (pixels[i] & 0xff00) >> 8;
        GLuint b = (pixels[i] & 0xff);
        
        pixels[i] = a << 24 | b << 16 | g << 8 | r;
    }
    
    GLuint result;
    glGenTextures(1, &result);
    glBindTexture(GL_TEXTURE_2D, result);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->w, texture->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    return result;
}

void Texture::enable() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
}

void Texture::disable() {
    glBindTexture(GL_TEXTURE_2D, 0);
}