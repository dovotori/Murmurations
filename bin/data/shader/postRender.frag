#version 330

in vec2 fragTexture;

uniform float cpt;
uniform vec2 resolution;
uniform sampler2D fboTexture;

out vec4 outputColor;


float random(vec2 scale, float seed, vec2 variations) {
	return fract( sin( dot( variations + seed, scale ) ) * 43758.5453 + seed );
}


void main() {
	
	vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture

	vec4 color = texture( fboTexture, st );

	float evolution = 0.5 + (cos(cpt * 0.1) * 0.5); 
	float n = random( vec2( 1.0 ), length( st ), st*evolution ); // noise
	n = 0.2 + n * 0.8; // attenuation du noise

	// alpha
	float alpha = n;
	if(color.x > 0.0){ alpha = 1.0; }

    outputColor = vec4(color.xyz, alpha);
    //outputColor = vec4(vec3(n), 1.0);

}