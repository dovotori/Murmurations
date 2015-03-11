#version 330 

in vec4 position;
in vec2 texcoord;

uniform sampler2D posTex;
uniform sampler2D velTex;

out vec3 geomVel;




void main() {

	vec2 st = texcoord;
    vec3 particulePos = texture(posTex, st).xyz; // recupére position de la texture
    vec3 particuleVel = texture(velTex, st).xyz; // recupére vitesse de la texture
    geomVel = particuleVel;
    gl_Position = vec4(particulePos, 1.0);

}
