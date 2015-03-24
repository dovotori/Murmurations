#version 330
layout(points) in; layout(points, max_vertices=1) out;

in vec3 geomVel[];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;

out vec4 fragColor;



void main()
{

    vec4 pos = gl_in[0].gl_Position; // va de 0 à 1

    pos.xyz -= 0.5; // -0.5 pour centrer  
    
    float profondeur = 1.0;//pos.z;
    vec3 couleurParticule = couleur.xyz;
    float alpha = (profondeur*0.4) + (couleur.w*0.6); 

    gl_Position = projection * view * model * pos;
    fragColor = vec4(couleurParticule, alpha);
    EmitVertex();

    EndPrimitive();
}
