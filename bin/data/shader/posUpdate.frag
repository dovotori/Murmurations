#version 330

in vec2 fragTexture;

uniform sampler2D prevPosData;    // recupere les positions precedentes par la texture
uniform sampler2D velData;        // recupere la texture de la vitesse
uniform float vitesseGenerale;
uniform int resolution;
uniform vec3 space;

out vec4 outputColor;


void main(void)
{

    vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture

    vec3 pos = texture( prevPosData, st ).xyz;
    vec3 vel = texture( velData, st ).xyz;

    pos += vel * vitesseGenerale;

    // RESPAWN A L'AUTRE BOUT
    if(pos.x > 0.5+(space.x*0.5)){ pos.x = 0.5-(space.x*0.5); }
    if(pos.y > 0.5+(space.y*0.5)){ pos.y = 0.5-(space.y*0.5); }
    if(pos.z > 0.5+(space.z*0.5)){ pos.z = 0.5-(space.z*0.5); }

    if(pos.x < 0.5-(space.x*0.5)){ pos.x = 0.5+(space.x*0.5); }
    if(pos.y < 0.5-(space.y*0.5)){ pos.y = 0.5+(space.y*0.5); }
    if(pos.z < 0.5-(space.z*0.5)){ pos.z = 0.5+(space.z*0.5); }

    outputColor = vec4(pos, 1.0);

}
