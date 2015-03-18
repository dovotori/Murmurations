#version 330
in vec2 fragTexture; in vec4 fragColor;
uniform sampler2D particuleTex;
out vec4 outputColor;
void main(){ outputColor = texture(particuleTex, fragTexture) * fragColor; }