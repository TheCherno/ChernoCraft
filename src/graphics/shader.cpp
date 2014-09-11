#include "shader.h"

Shader* Shader::BLOCK;

Shader::Shader(const char *vertex, const char *fragment) {
    std::string vsrc = FileUtils::read_file(vertex);
    std::string fsrc = FileUtils::read_file(fragment);
    const char *vs = vsrc.c_str();
    const char *fs = fsrc.c_str();
    shader = load(vs, fs);
}

Shader::Shader(std::string vertex_source, std::string fragment_source, std::string name) {
    const char *vs = vertex_source.c_str();
    const char *fs = fragment_source.c_str();
    shader = load(vs, fs);
}

void Shader::LOAD() {
    BLOCK = new Shader("shaders/shader.vert", "shaders/shader.frag");
    BLOCK->enable();
    BLOCK->set_uniform_matrix("pr_matrix", glm::perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));
    BLOCK->set_uniform_matrix("vw_matrix", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -500.0f)));
    BLOCK->disable();
}

GLuint Shader::load(const char *vs, const char *fs) {
    GLuint program = glCreateProgram();
    
    GLuint vert = glCreateShader(GL_VERTEX_SHADER);
    GLuint frag = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vert, 1, &vs, NULL);
    glCompileShader(vert);
    
    GLint result;
    glGetShaderiv(vert, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(vert, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> error(length);
        glGetShaderInfoLog(vert, length, &length, &error[0]);
        std::cerr << &error[0] << std::endl;
        glDeleteShader(vert);
        throw new std::runtime_error("Could not compile vertex shader!");
    }
    
    glShaderSource(frag, 1, &fs, NULL);
    glCompileShader(frag);
    
    glGetShaderiv(frag, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(frag, GL_INFO_LOG_LENGTH, &length);
        std::vector<char> error(length);
        glGetShaderInfoLog(frag, length, &length, &error[0]);
        std::cerr << &error[0] << std::endl;
        glDeleteShader(frag);
        throw new std::runtime_error("Could not compile fragment shader!");
    }
    
    glAttachShader(program, vert);
    glAttachShader(program, frag);
    
    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vert);
    glDeleteShader(frag);
    
    return program;
}

GLint Shader::get_uniform(const GLchar *name) {
    GLint result = glGetUniformLocation(shader, name);
    if (result == -1) std::cerr << "Could not find location for '" << name << "'" << std::endl;
    return result;
}

void Shader::set_uniform_matrix(const char *name, glm::mat4 matrix) {
    glUniformMatrix4fv(get_uniform(name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_uniform_int(const char *name, GLuint data) {
    glUniform1i(get_uniform(name), data);
}

void Shader::set_uniform_float1(const char *name, float data) {
    glUniform1f(get_uniform(name), data);
}

void Shader::set_uniform_float2(const char *name, glm::vec2 data) {
    glUniform2f(get_uniform(name), data.x, data.y);
}

void Shader::set_uniform_float3(const char *name, glm::vec3 data) {
    glUniform3f(get_uniform(name), data.x, data.y, data.z);
}

void Shader::set_uniform_float4(const char *name, glm::vec4 data) {
    glUniform4f(get_uniform(name), data.x, data.y, data.z, data.w);
}

void Shader::enable() {
    glUseProgram(shader);
}

void Shader::disable() {
    glUseProgram(0);
}