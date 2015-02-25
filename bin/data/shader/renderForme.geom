#version 330
layout(points) in; layout(triangle_strip, max_vertices=33) out;

in vec3 geomVel[];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;
uniform float tailleParticule;

out vec4 fragColor;


float map(float valeur, float minRef, float maxRef, float minDest, float maxDest)
{ return minDest + (valeur - minRef) * (maxDest - minDest) / (maxRef - minRef); }



void main()
{

    vec4 pos = gl_in[0].gl_Position; // va de 0 à 1

    float profondeur = pos.z;
    vec3 couleurParticule = couleur.xyz;
    float alpha = (profondeur*0.4) + (couleur.w*0.6); 
    float M_PI = 3.141592653589793238462643383279502884;
    float angleRotation = 1.0;
    float taille = (0.4 + (profondeur * 0.6)) * tailleParticule;
    int details = 10;

    mat4 rotationForme = mat4(
        cos(angleRotation), -sin(angleRotation), 0.0, 0.0,  
        sin(angleRotation), cos(angleRotation), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0);

    mat4 translationForme = mat4(
        1.0, 0.0, 0.0, pos.x-0.5, // -0.5 pour centrer  
        0.0, 1.0, 0.0, pos.y-0.5,
        0.0, 0.0, 1.0, pos.z-0.5,
        0.0, 0.0, 0.0, 1.0);

    mat4 camera = projection * view * model;

    int i;
    for(i = 0; i < details; i++) {

        // CENTRE CERCLE
        vec4 forme = /* rotationForme */ vec4(0.0, 0.0, 0.0, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        // POINT 1
        float angle = map(i, 0, details, 0.0, M_PI*2);
        float x = cos(angle) * taille;// * 0.2;
        float y = sin(angle) * taille;
        forme = /* rotationForme */vec4(x, y, 0.0, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        // POINT 2
        angle = map(i+1, 0, details, 0.0, M_PI*2);
        x = cos(angle) * taille;// * 0.2;
        y = sin(angle) * taille;
        forme = /* rotationForme */vec4(x, y, 0.0, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        EndPrimitive();

    }

}
