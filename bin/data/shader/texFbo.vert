#version 330


in vec4 position;
in vec2 texcoord;

out vec2 fragTexture;

void main()
{
	fragTexture = texcoord;
	vec4 npos = vec4(position.xyz, 1.0);

	/* ON REPLACE LA TEXTURE DE 0,1 à -1,1 pour le FBO d'OF */
	npos.x = ( npos.x * 2.0 ) - 1.0;
	npos.y = ( npos.y * 2.0 ) - 1.0;
	gl_Position = npos;

}

