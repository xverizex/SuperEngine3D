#version 460 core

precision highp float;

out vec4 FragColor;

in vec2 tex;

uniform sampler2D s_texture;

void main ()
{
	FragColor = texture (s_texture, vec2 ( tex.x, 1.0 - tex.y));
}
