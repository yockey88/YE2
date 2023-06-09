#version 460 core
layout (location = 0) in vec2 pos;
layout (location = 1) in vec2 uv;

out vec2 tex_coords;

void main() {
    gl_Position = vec4(pos, 0.0, 1.0);
    tex_coords = uv;
}