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

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

void main() {
    // ambient
    vec3 ambient = light.ambient * material.ambient; // * vec3(out_color);

    // diffuse
    vec3 norm = normalize(out_normal);
    vec3 light_dir = normalize(light.position - frag_pos);
    float diff = max(dot(norm , light_dir) , 0.0);
    vec3 diffuse = light.diffuse * (diff * material.diffuse);

    // specular
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir , norm);
    float spec = pow(max(dot(view_dir , reflect_dir) , 0.0) , material.shininess);
    vec3 specular = light.specular * (spec * material.specular);

    vec3 result = ambient + diffuse + specular;
    frag_color = vec4(result , 1.0);
}