#version 460 core

layout (location = 0) in vec3 aPos;

smooth out vec4 vSmoothColor;

uniform mat4 view;
uniform mat4 translate;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 scale;

uniform float time;

const vec3 a = vec3(0, 2, 0);
vec3 g = vec3(0, -9.8, 0);

const float rate = 1/500.0;
const float life = 2;

const float PI = 3.14159;
const float TWO_PI = 2 * PI;

const vec3 RED = vec3(1, 0, 0);
const vec3 GREEN = vec3(0, 1, 0);
const vec3 YELLOW = vec3(1, 1, 0);

float rand(vec2 co) {
	return fract (sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
}

vec3 uniformRadomDir(vec2 v, out vec2 r) {
	r.x = rand(v.xy);
	r.y = rand(v.yx);
	float theta = mix(0.0, PI / 6.0, r.x);
	float phi = mix (0.0, TWO_PI, r.y);
	return vec3(sin(theta) * cos(phi), cos(theta), sin(theta) * sin(phi));
}

void main() {
	vec3 pos = aPos;
	float t = gl_VertexID * rate;

	float alpha = 1;

	if (time > t) {
		float dt = mod((time - t), life);
		vec2 xy = vec2(gl_VertexID, t);
		vec2 rdm = vec2(0);
		pos = ((uniformRadomDir(xy, rdm) + 0.5 * a * dt) * dt);
		alpha = 1.0 - (dt / life);
	}

	vSmoothColor = vec4(mix(RED, YELLOW, alpha), alpha);

	gl_Position = projection * view * translate * scale * model * vec4(pos, 1.0);
}