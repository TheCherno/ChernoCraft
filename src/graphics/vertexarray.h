#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

class VertexArray {
private:
    GLuint vao, ibo;
    GLsizei count;
    GLuint compile(GLfloat *vertices, GLuint *indices, int count);
public:
    VertexArray(GLfloat *vertices, GLuint *indices, int count);
    void render();
};