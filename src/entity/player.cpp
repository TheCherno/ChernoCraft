#include "player.h"
#include "../level/level.h"

Player::Player(glm::vec3 position) {
    this->position = position;
    this->position.y = -this->position.y;
    shader = Shader::BLOCK;
    
    const GLfloat TSIZE = 0.2f;
    GLfloat vertices[4 * 3] = {
        -TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f,
        -TSIZE / 2.0f,  TSIZE / 2.0f, 0.0f,
         TSIZE / 2.0f,  TSIZE / 2.0f, 0.0f,
         TSIZE / 2.0f, -TSIZE / 2.0f, 0.0f
    };
    GLuint indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
    
    target = new VertexArray(vertices, indices, (GLfloat*) NULL, 4 * 3, 6);
}

void Player::update() {
    if (Input::key_pressed(SDL_SCANCODE_W)) {
        float xa = -sin(Math::to_radians(rotation.y)) * speed;
        float za = cos(Math::to_radians(rotation.y)) * speed;
        glm::vec3 pos = glm::vec3(position.x, position.y + 8.0f, position.z);
        glm::vec3 rot = glm::vec3(xa, 0.0f, za);
//        if (level->raycast_block_id(position, rot, 32.0f) < 2 && level->raycast_block_id(pos, rot, 32.0f) < 2) {
            position.x += xa;
            position.z += za;
//        }
    }
    if (Input::key_pressed(SDL_SCANCODE_S)) {
        float xa = sin(Math::to_radians(rotation.y)) * speed;
        float za = -cos(Math::to_radians(rotation.y)) * speed;
      //  if (level->raycast_collision(position, glm::vec3(xa, za, 0.0f)) < 2) {
            position.x += xa;
            position.z += za;
      //  }
    }
    if (Input::key_pressed(SDL_SCANCODE_A)) {
        float xa = -sin(Math::to_radians(rotation.y - 90.0f)) * speed;
        float za = cos(Math::to_radians(rotation.y - 90.0f)) * speed;
     //  if (level->raycast_collision(position, glm::vec3(xa, za, 0.0f)) < 2) {
            position.x += xa;
            position.z += za;
     //   }
    }
    if (Input::key_pressed(SDL_SCANCODE_D)) {
        float xa = -sin(Math::to_radians(rotation.y + 90.0f)) * speed;
        float za = cos(Math::to_radians(rotation.y + 90.0f)) * speed;
       // if (level->raycast_collision(position, glm::vec3(xa, za, 0.0f)) < 2) {
            position.x += xa;
            position.z += za;
      //  }
    }
    glm::vec3 gravity = glm::vec3(0, -1, 0);
    bool block = level->raycast_block_id(position, gravity, 10.0f) > 1;
    if (!block || jumping) position.y -= dy;
    if (dy < -1.0f) dy = -1.0f;
    if (dy > 2.0f) dy = 2.0f;
    
//    if (position.y > -48.0f) position.y = -48.0f;
    if (jumping) dy += 0.5f;
    if (dy > JUMP_HEIGHT) jumping = false;
    if (!jumping && dy > -JUMP_HEIGHT) dy -= 0.15f;
    if (Input::key_pressed(SDL_SCANCODE_SPACE) && !jumping && block) {
        jumping = true;
    }
    if (Input::key_typed(SDL_SCANCODE_F)) {
        light = !light;
    }
    if (Input::mouse_grabbed()) {
        rotation.x -= Input::get_DY() * mouse_sensitivity;
        rotation.y -= Input::get_DX() * mouse_sensitivity;
    }
    if (rotation.x < -90.0f) rotation.x = -90.0f;
    if (rotation.x >  90.0f) rotation.x =  90.0f;
    
    glm::vec3 b = level->raycast_block(position, rotation);
    level->select_block(b);
    if (Input::mouse_clicked(SDL_BUTTON_LEFT)) {
        unsigned short& rid = level->pick_block(position, rotation);
        if (rid != Level::NULL_BLOCK) rid = 1;
    } else if (Input::mouse_clicked(SDL_BUTTON_RIGHT)) {
        // Place block!
        unsigned short& bid = level->raycast_pre_block_id(position, rotation);
        if (bid == 1) bid = 2;
    }
}

void Player::render() {
    shader->enable();
    glm::mat4 vw_matrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    vw_matrix *= glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    vw_matrix *= glm::translate(glm::mat4(1.0f), position);
    shader->set_uniform_matrix("vw_matrix", vw_matrix);
    shader->set_uniform_float3("player_pos", -position);
    if (light) shader->set_uniform_float1("light_on", 1);
    else shader->set_uniform_float1("light_on", 0);
    shader->disable();
    Shader::HUD->enable();
    target->render();
    Shader::HUD->disable();
}
