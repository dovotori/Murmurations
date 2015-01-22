#version 330

in vec2 fragTexture;

out vec4 outputColor;


void main(void)
{
	vec4 color = vec4(1.0, 0.0, 0.0, 1.0);

	if(fragTexture.x > 0.5){
		color = vec4(0.0, 1.0, 0.0, 1.0);
	}
    
    outputColor = color;
}