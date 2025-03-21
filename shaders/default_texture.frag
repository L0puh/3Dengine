#version 330 core

out vec4 color;
uniform vec3 _color;
in vec2 _tex_coord;

uniform sampler2D _texture;

void main() {
   color = texture(_texture, _tex_coord);
}
