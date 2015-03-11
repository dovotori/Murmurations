#version 330
layout(points) in; layout(triangle_strip, max_vertices=60) out;


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


    float X = 0.525731112119133606;
    float Z = 0.850650808352039932;
    vec3 vdata[12];
    vdata[0] = vec3(-X, 0.0, Z); vdata[1] = vec3(X, 0.0, Z); vdata[2] = vec3(-X, 0.0, -Z); vdata[3] = vec3(X, 0.0, -Z);
    vdata[4] = vec3(0.0, Z, X); vdata[5] = vec3(0.0, Z, -X); vdata[6] = vec3(0.0, -Z, X); vdata[7] = vec3(0.0, -Z, -X);
    vdata[8] = vec3(Z, X, 0.0); vdata[9] = vec3(-Z, X, 0.0); vdata[10] = vec3(Z, -X, 0.0); vdata[11] = vec3(-Z, -X, 0.0);

    vec3 tindices[20];
    tindices[0] = vec3(0, 4, 1); 
    tindices[1] = vec3( 0, 9, 4 ); 
    tindices[2] = vec3( 9, 5, 4 ); 
    tindices[3] = vec3( 4, 5, 8 ); 
    tindices[4] = vec3( 4, 8, 1 );
    tindices[5] = vec3( 8, 10, 1 ); 
    tindices[6] = vec3( 8, 3, 10 ); 
    tindices[7] = vec3( 5, 3, 8 ); 
    tindices[8] = vec3( 5, 2, 3 ); 
    tindices[9] = vec3( 2, 7, 3 );
    tindices[10] = vec3( 7, 10, 3 ); 
    tindices[11] = vec3( 7, 6, 10 ); 
    tindices[12] = vec3( 7, 11, 6 ); 
    tindices[13] = vec3( 11, 0, 6 ); 
    tindices[14] = vec3( 0, 1, 6 );
    tindices[15] = vec3( 6, 1, 10 ); 
    tindices[16] = vec3( 9, 0, 11 ); 
    tindices[17] = vec3( 9, 11, 2 ); 
    tindices[18] = vec3( 9, 2, 5 ); 
    tindices[19] = vec3( 7, 2, 11 );
    


    int i, j; 
    for(i = 0; i < 20; i++) {

        vec3 ind = tindices[i];

        vec3 posForm = vdata[int(ind.x)] * taille;
        vec4 forme = vec4(posForm, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        posForm = vdata[int(ind.y)] * taille;
        forme = vec4(posForm, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        posForm = vdata[int(ind.z)] * taille;
        forme = vec4(posForm, 1.0) * translationForme;
        gl_Position = camera * forme;
        fragColor = vec4(couleurParticule, alpha);
        EmitVertex();

        EndPrimitive();

    }

}
