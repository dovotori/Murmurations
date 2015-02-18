#version 330

in vec2 fragTexture;

uniform sampler2D tex;
uniform vec2 resolution;
uniform float alpha;

out vec4 outputColor;

void main()
{

	vec2 st = fragTexture;
	vec4 color = texture(tex, st);
    outputColor = vec4(color.xyz, alpha);

}
