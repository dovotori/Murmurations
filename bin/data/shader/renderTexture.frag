#version 330

in vec2 fragTexture;

uniform sampler2D particuleTex;

out vec4 outputColor;

void main() {
    outputColor = texture(particuleTex, fragTexture);
}