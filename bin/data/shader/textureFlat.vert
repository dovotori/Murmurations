#version 330

in vec4 position;
in vec2 texcoord;

out vec2 fragTexture;

void main() {

	fragTexture = texcoord;
	gl_Position = position;
}

