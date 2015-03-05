#version 330

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

in vec4 position;

void main(){

	gl_Position = projection * view * model * position;

}

