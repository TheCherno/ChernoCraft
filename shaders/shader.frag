#version 330 core

layout (location = 0) out vec4 color;
uniform vec3 block_color;

uniform vec3 player_pos;
vec3 light = vec3(2.0, 7.0, 2.0);

in DATA {
    vec3 position;
} fs_in;

void main() {
    //color = vec4(0.2, 0.3, 0.8, 1.0);
    float intensity = 1.0 / length(player_pos - fs_in.position);
    vec3 bc = block_color * fs_in.position / 30.0f;
    bc *= intensity * 20.0 - 0.2;
    color = vec4(bc, 1.0);
}