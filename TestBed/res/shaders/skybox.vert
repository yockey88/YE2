#version 460 core
layout (location = 0) in vec3 pos;

out vec3 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main () {
    vec4 pos2 = proj * view * model * vec4(pos , 1.0); 
    gl_Position = pos2.xyww; // proj * view * vec4(pos , 1.0); 
    tex_coords = pos;
}