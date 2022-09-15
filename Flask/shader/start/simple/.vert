#version 450
#pragma vertex

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

layout(location = 0) out vec3 out_colour;

void main() {
	gl_Position = vec4(position, 1.0);
	out_colour = colour;
}
