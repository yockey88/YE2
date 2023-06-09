#version 460 core
in vec4 out_color;
in vec3 frag_pos;
in vec3 out_normal;
in vec3 in_tangent;
in vec3 in_bitangent;
in vec2 tex_coords;

out vec4 frag_color;

uniform vec3 view_pos;
uniform sampler2D tex;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform mat4 model;
uniform Light light;

void main() {
    frag_color = vec4(light.diffuse , 1.0);
}