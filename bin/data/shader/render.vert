#version 330

in vec4 position;
in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform sampler2D posTex;
uniform vec3 couleur;
uniform vec3 screen;
uniform float resolution;

out vec4 geomColor;
out float geomZ;
out float geomAngle;



float map(float valeur, float minRef, float maxRef, float minDest, float maxDest)
{
    return minDest + (valeur - minRef) * (maxDest - minDest) / (maxRef - minRef);
}


void main() {

	// map les coor de texture à 0,1
	vec2 st = texcoord / resolution;

    // recupére position de la texture
    vec3 particulePos = texture(posTex, st).xyz;

    geomAngle = texture(posTex, st).a;

    geomZ = particulePos.z;
    geomColor = vec4(couleur, 1.0);

    // map la position dans le nouvel espace
    particulePos.x = (particulePos.x * screen.x) - (screen.x / 2.0);
    particulePos.y = (particulePos.y * screen.y) - (screen.y / 2.0);
    particulePos.z = (particulePos.z * screen.z) - (screen.z / 2.0);

    gl_Position = projection * view * model * vec4(particulePos, 1.0);
}
