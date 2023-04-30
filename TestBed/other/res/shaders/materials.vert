#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;
layout (location = 5) in vec2 uvs;
layout (location = 6) in float opacity;

out vec4 out_color;
out vec3 frag_pos;
out vec3 out_normal;
out vec3 out_tangent;
out vec3 out_bitangent;
out vec2 tex_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    frag_pos = vec3(model * vec4(pos, 1.0));
    out_normal = mat3(transpose(inverse(model))) * normal;

    gl_Position = proj * view * vec4(frag_pos , 1.0);

    out_color = vec4(color, opacity);
    out_tangent = tangent;
    out_bitangent = bitangent;
    tex_coords = uvs;
}