#version 330
in vec4 fragColor;
out vec4 outputColor;
void main(){ outputColor = vec4(fragColor.xyz, 0.5); }