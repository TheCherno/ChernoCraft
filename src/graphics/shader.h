#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <OpenGL/gl3.h>
#include "../utils/fileutils.h"
#include "../utils/glm.h"

class Shader {
public:
    static Shader *BLOCK;
private:
    GLuint shader;
    GLuint load(const char *vs, const char *fs);
public:
    Shader(const char *vertex, const char *fragment);
    Shader(std::string vertex_source, std::string fragment_source, std::string name);
    static void LOAD();
    static void DESTROY();
    GLint get_uniform(const char *name);
    void set_uniform_matrix(const char *name, glm::mat4 matrix);
    void set_uniform_int(const char *name, GLuint data);
    void set_uniform_float1(const char *name, float data);
    void set_uniform_float2(const char *name, glm::vec2 data);
    void set_uniform_float3(const char *name, glm::vec3 data);
    void set_uniform_float4(const char *name, glm::vec4 data);
    void enable();
    void disable();
};