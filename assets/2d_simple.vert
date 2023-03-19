#version 460 core
layout (location = 0) in vec3 position_vertex;
layout (location = 1) in vec2 tex_coord;

uniform mat4 pos;
uniform mat4 ortho;
uniform mat4 scale;
uniform mat4 model;

out vec2 tex;

void main ()
{
	gl_Position = ortho * pos * model * scale * vec4 (position_vertex, 1.0f);
	tex = tex_coord;
}