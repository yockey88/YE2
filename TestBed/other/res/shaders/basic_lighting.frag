#version 460 core
in vec4 out_color;
in vec3 frag_pos;
in vec3 out_normal;
in vec2 tex_coords;

out vec4 frag_color;

uniform vec3 light_pos;
uniform vec3 view_pos;
uniform vec3 light_col;
uniform vec3 obj_col;

uniform sampler2D tex;

void main() {
    float ambient_strength = 0.1;
    vec3 ambient = ambient_strength * light_col;
    
    // diffuse
    vec3 norm = normalize(out_normal);
    vec3 light_dir = normalize(light_pos - frag_pos);
    float diff = max(dot(norm , light_dir), 0.0);
    vec3 diffuse = diff * light_col;

    // specular
    float specular_strength = 0.5;
    vec3 view_dir = normalize(view_pos - frag_pos);
    vec3 reflect_dir = reflect(-light_dir , norm);
    float spec = pow(max(dot(view_dir , reflect_dir) , 0.0) , 32);
    vec3 specular = specular_strength * spec * light_col;

    vec3 result = (ambient + diffuse + specular) * obj_col;
    frag_color = vec4(result , 1.0) * texture(tex, tex_coords);
}