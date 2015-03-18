#version 330

in vec2 fragTexture;

uniform float cpt;
uniform float noiseInfluence;
uniform float noiseScale;
uniform vec2 resolution;
uniform sampler2D fboTexture;

out vec4 outputColor;


float random(vec2 scale, float seed, vec2 variations) 
{ return fract( sin( dot( variations + seed, scale ) ) * 43758.5453 + seed ); }


vec4 blurV(vec2 st)
{
   vec4 color = vec4(0.0);

   float blur = 4.0 / resolution.x;
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   color += texture(fboTexture, vec2(st.x, st.y - 4.0*blur)) * 0.05;
   color += texture(fboTexture, vec2(st.x, st.y - 3.0*blur)) * 0.09;
   color += texture(fboTexture, vec2(st.x, st.y - 2.0*blur)) * 0.12;
   color += texture(fboTexture, vec2(st.x, st.y - blur)) * 0.15;
   color += texture(fboTexture, vec2(st.x, st.y)) * 0.16;
   color += texture(fboTexture, vec2(st.x, st.y + blur)) * 0.15;
   color += texture(fboTexture, vec2(st.x, st.y + 2.0*blur)) * 0.12;
   color += texture(fboTexture, vec2(st.x, st.y + 3.0*blur)) * 0.09;
   color += texture(fboTexture, vec2(st.x, st.y + 4.0*blur)) * 0.05;
 
   return color;
}


vec4 noiseEffect(vec2 st, vec4 color)
{

	float alpha = 1.0;
	if(noiseInfluence < 2.0) {
		// fond
		if(color.x <= 0.0)
		{
			float evolution = 0.5 + (cos(cpt) * 0.5); 
			alpha = random( vec2( noiseScale ), length( st ), st * evolution ); // noise // scale est cool, fait du moirage en dessous de 1
			alpha = (1.0 - noiseInfluence) + (alpha * noiseInfluence); // attenuation du noise
			alpha = 0.0;
		} 
	} else {
		// fond 
		if(color.x <= 0.0){ alpha = 0.0; }
	}
	return vec4(color.xyz, alpha);
}


void main() {
	
	vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture
	vec4 color = texture( fboTexture, st );

	//vec4 colorNoise = noiseEffect(st, color);
	//vec4 colorBlur = blurV(st);

	outputColor = color;

}