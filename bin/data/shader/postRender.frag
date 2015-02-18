#version 330

in vec2 fragTexture;

uniform float cpt;
uniform float noiseInfluence;
uniform float noiseScale;
uniform vec2 resolution;
uniform sampler2D fboTexture;

out vec4 outputColor;


float random(vec2 scale, float seed, vec2 variations) {
	return fract( sin( dot( variations + seed, scale ) ) * 43758.5453 + seed );
}


void main() {
	
	vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture

	vec4 color = texture( fboTexture, st );


	float alpha = 1.0;
	if(noiseInfluence < 2.0) {
		if(color.x <= 0.0)
		{
			float evolution = 0.5 + (cos(cpt) * 0.5); 
			alpha = random( vec2( noiseScale ), length( st ), st * evolution ); // noise // scale est cool, fait du moirage en dessous de 1
			alpha = (1.0 - noiseInfluence) + (alpha * noiseInfluence); // attenuation du noise
		} 
	} else {
		if(color.x <= 0.0){ alpha = 0.0; }
	}

	

    outputColor = vec4(color.xyz, alpha);
    //outputColor = vec4(vec3(n), 1.0);

}