#version 330

in vec2 fragTexture;

uniform sampler2D tex;
uniform vec2 resolution;
uniform float alpha;

out vec4 outputColor;

void main()
{

	float apparition = 0.5 + (cos(alpha) * 0.5); 

	vec2 st = fragTexture;
	vec4 color = texture(tex, st);
    outputColor = vec4(color.xyz, apparition);

}
