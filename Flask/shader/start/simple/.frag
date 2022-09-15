#version 450
#pragma fragment

layout(location = 0) in vec3 colour;

layout(location = 0) out vec4 out_colour;

void main() {
	out_colour = vec4(colour, 1.0);
}
