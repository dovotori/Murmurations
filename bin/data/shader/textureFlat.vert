#version 330

in vec4 position;
in vec2 texcoord;

out vec2 fragTexture;

void main() {

	fragTexture = texcoord;
	gl_Position = vec4(position.xyz, 1.0);
}

