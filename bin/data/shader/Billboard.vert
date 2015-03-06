#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4  position;
in vec4  color;

out vec4 colorVarying;

void main() {
	vec3 npos = position.xyz - vec3(0.5);
	gl_Position = projection * view * model  * vec4(npos, 1.0);
	colorVarying = color;
}





