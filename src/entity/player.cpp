#include "player.h"

Player::Player(glm::vec3 position) {
    this->position = position;
    this->position.y = -this->position.y;
    shader = Shader::BLOCK;
}

void Player::update() {
    if (Input::key_pressed(SDL_SCANCODE_W)) {
        position.x -= sin(Math::to_radians(rotation.y));
        position.z += cos(Math::to_radians(rotation.y));
    }
    if (Input::key_pressed(SDL_SCANCODE_S)) {
        position.x += sin(Math::to_radians(rotation.y));
        position.z -= cos(Math::to_radians(rotation.y));
    }
    if (Input::key_pressed(SDL_SCANCODE_A)) {
        position.x -= sin(Math::to_radians(rotation.y - 90.0f));
        position.z += cos(Math::to_radians(rotation.y - 90.0f));
    }
    if (Input::key_pressed(SDL_SCANCODE_D)) {
        position.x -= sin(Math::to_radians(rotation.y + 90.0f));
        position.z += cos(Math::to_radians(rotation.y + 90.0f));
    }
    rotation.x -= Input::get_DY() * mouse_sensitivity;
    rotation.y -= Input::get_DX() * mouse_sensitivity;
    
    if (rotation.x < -90.0f) rotation.x = -90.0f;
    if (rotation.x >  90.0f) rotation.x =  90.0f;
}

void Player::render() {
    shader->enable();
    glm::mat4 vw_matrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    vw_matrix *= glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    vw_matrix *= glm::translate(glm::mat4(1.0f), position);
    shader->set_uniform_matrix("vw_matrix", vw_matrix);
    shader->set_uniform_float3("player_pos", -position);
    shader->disable();
}
