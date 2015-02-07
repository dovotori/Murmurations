#version 330

in vec2 fragTexture;

uniform sampler2D prevVelData;   // vitesse precedente
uniform sampler2D posData;      // position
uniform int resolution;

out vec4 outputColor;




void main(void)
{

    vec2 st = fragTexture * resolution;    // recupere la particule

    vec3 pos = texture(posData, st).xyz;      // sa position
    vec3 vel = texture(prevVelData, st).xyz;  // sa precedente vitesse

    outputColor = vec4(vel, 1.0);

}


