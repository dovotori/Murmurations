#version 330
layout(points) in; layout(points, max_vertices=1) out;

in vec3 geomVel[];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;
uniform float tailleParticule;

out vec4 fragColor;



void main()
{

    vec4 pos = gl_in[0].gl_Position; // va de 0 à 1

    pos.x -= 0.5; // -0.5 pour centrer  
    pos.y -= 0.5;
    pos.z -= 0.5;

    float profondeur = pos.z;
    vec3 couleurParticule = couleur.xyz;
    float alpha = (profondeur*0.4) + (couleur.w*0.6); 

    gl_Position = projection * view * model * pos;
    fragColor = vec4(couleurParticule, alpha);
    EmitVertex();

    EndPrimitive();
}
