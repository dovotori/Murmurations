#version 330

in vec2 fragTexture;

uniform sampler2D tex;
uniform vec2 resolution;
uniform float alpha;
uniform float cpt;
uniform float noiseInfluence;
uniform float noiseScale;

out vec4 outputColor;

float random(vec2 scale, float seed, vec2 variations) 
{ return fract( sin( dot( variations + seed, scale ) ) * 43758.5453 + seed ); }



float noiseEffect(vec2 st)
{
	float evolution = 0.5 + (cos(cpt) * 0.5); 
	float alpha = random( vec2( noiseScale ), length( st ), st * evolution ); // noise // scale est cool, fait du moirage en dessous de 1
	alpha = (1.0 - noiseInfluence) + (alpha * noiseInfluence); // attenuation du noise
		
	return alpha;
}


void main()
{

	vec4 color = texture(tex, fragTexture);
	float n = noiseEffect(fragTexture);
    outputColor = vec4(color.xyz*n, alpha);

}
