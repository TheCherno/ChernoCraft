#version 330 core

layout (location = 0) out vec4 color;
uniform vec3 block_color;

uniform vec3 player_pos;
uniform float light_on;
uniform float selected;
vec3 light = vec3(2.0, 7.0, 2.0);

in DATA {
    vec3 position;
} fs_in;

void main() {
    //color = vec4(0.2, 0.3, 0.8, 1.0);
    float intensity = 2.0 / length(player_pos - fs_in.position);
    vec3 bc = block_color * fs_in.position / 60.0f;
    float i = intensity * 20.0 - 0.2;
    if (i > 1.8) i = 1.8;
    bc *= i;
    if (light_on == 0.0) bc *= 0.1;
    color = vec4(bc, 1.0);
    if (selected == 1.0) color += 0.5;
}