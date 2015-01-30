#version 330


in vec2 fragTexture;

uniform sampler2D prevPosData;    // recupere les positions precedentes par la texture
uniform sampler2D velData;        // recive the velocity texture
uniform float timestep;
uniform int resolution;

out vec4 outputColor;


void main(void)
{

    vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture

    vec3 pos = texture( prevPosData, st ).xyz;
    vec3 vel = texture( velData, st ).xyz;

    pos += vel * timestep;

    // RESPAWN A L'AUTRE BOUT
    if(pos.x > 1.0){ pos.x = 0.0; }
    if(pos.y > 1.0){ pos.y = 0.0; }
    if(pos.z > 1.0){ pos.z = 0.0; }

    if(pos.x < 0.0){ pos.x = 1.0; }
    if(pos.y < 0.0){ pos.y = 1.0; }
    if(pos.z < 0.0){ pos.z = 1.0; }

    outputColor = vec4(pos, 1.0);

}
