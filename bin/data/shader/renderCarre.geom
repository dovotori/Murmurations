#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;
uniform float tailleParticule;

out vec4 fragColor;



void main()
{

	vec4 pos = gl_in[0].gl_Position;

    pos.x -= 0.5; // -0.5 pour centrer  
    pos.y -= 0.5;
    pos.z -= 0.5;

    float profondeur = pos.z;
    float taille = (0.6 + (profondeur * 0.4)) * tailleParticule;
    float alpha = 0.6 + (profondeur * 0.4);

    mat4 camera = projection * view * model;

    // centre la forme
    pos.x -= taille;
    pos.y -= taille;

    // 1EME TRIANGLE
    gl_Position = camera * pos;
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    pos.x += taille;
    gl_Position = camera * pos;
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    pos.x -= taille;
    pos.y += taille;
    gl_Position = camera * pos;
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    pos.x += taille;
    gl_Position = camera * pos;
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    EndPrimitive();


}
