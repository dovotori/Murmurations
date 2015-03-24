#version 330

in vec2 fragTexture;

uniform vec2 resolution;
uniform sampler2D fboTexture;
uniform sampler2D fboTexture2;

out vec4 outputColor;


void main() 
{
	vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture
	vec4 color = texture( fboTexture, st );
	vec4 color2 = texture( fboTexture2, st );
	outputColor = color + (color2 * 2.0); 
}