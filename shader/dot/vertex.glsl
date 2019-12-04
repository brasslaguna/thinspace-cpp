
#version 300 es

precision highp float;

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texture;

out vec2 texture_;

uniform mat4 model;

void main() {

	gl_Position = model * vec4(position, 1);
	texture_ = texture;

}
