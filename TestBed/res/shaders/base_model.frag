#version 460 core
in vec4 out_color;
in vec3 frag_pos;
in vec3 out_normal;
in vec2 tex_coords;

out vec4 frag_color;

uniform vec3 view_pos;
uniform sampler2D texture_diffuse1;

void main() {
    frag_color = texture(texture_diffuse1 , tex_coords);
}