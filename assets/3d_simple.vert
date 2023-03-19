#version 460 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex_coord;
layout (location = 2) in vec3 normals;

uniform mat4 projection;
uniform mat4 translate;
uniform mat4 view;
uniform mat4 model;
uniform mat4 rotate;

out vec4 vertexColor;
out vec2 tex;

void main ()
{
	gl_Position = projection * view * translate * rotate * model * vec4 (pos, 1.0);
	tex = tex_coord;
}
