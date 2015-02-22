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

    // angle de direction passé dans l'alpha de la texture 
    float M_PI = 3.141592653589793238462643383279502884;
    vec3 dirBase = vec3(0, -1, 0);
    float angle = dot(dirBase, vel);
    //float cosAngle = dot / (length(dirBase) * length(vel));
    //float angleRadian = acos(cosAngle);
    //float angle = (angleRadian * 180) / M_PI;
    //var sens = signe( (this.x * v.y) + (this.y * v.x) ); // sens de l'angle

    outputColor = vec4(pos * ( 1.0 / angle ), angle); // w est le facteur de normalisation

}
