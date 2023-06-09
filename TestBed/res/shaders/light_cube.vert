#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in vec2 uvs;
layout (location = 6) in float opacity;

out vec4 out_color;
out vec3 out_normal;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
	gl_Position = proj * view * model * vec4(pos , 1.0);
    out_color = vec4(color , opacity);
    out_normal = normal;
    tex_coords = uvs;
}