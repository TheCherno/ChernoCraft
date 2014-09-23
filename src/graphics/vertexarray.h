#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <OpenGL/gl3.h>

class VertexArray {
private:
    GLuint vao, ibo;
    GLsizei count;
    GLuint compile(GLfloat *vertices, GLuint *indices, GLsizei vcount, GLsizei icount);
    GLuint compile(GLfloat *vertices, GLuint *indices, GLfloat *tcs, GLsizei vcount, GLsizei icount);
    GLuint compile(GLfloat *vertices, GLuint *indices, GLfloat *normals, GLfloat *tcs, GLsizei vcount, GLsizei icount);
public:
    VertexArray(GLfloat *vertices, GLuint *indices, GLsizei vcount, GLsizei icount);
    VertexArray(GLfloat *vertices, GLuint *indices, GLfloat *tcs, GLsizei vcount, GLsizei icount);
    VertexArray(GLfloat *vertices, GLuint *indices, GLfloat *normals, GLfloat *tcs, GLsizei vcount, GLsizei icount);
    void render();
};