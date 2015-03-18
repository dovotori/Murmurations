#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;
uniform vec3 cameraPos;
uniform float tailleParticule;

out vec4 fragColor;



void main()
{

	vec4 pos = gl_in[0].gl_Position;

    pos.x -= 0.5; // -0.5 pour centrer  
    pos.y -= 0.5;
    pos.z -= 0.5;

    float profondeur = pos.z;
    float taille = (0.4 + (profondeur * 0.6)) * tailleParticule;
    float alpha = couleur.a;

    mat4 gVP = projection * view;
    vec3 Pos = pos.xyz;
    vec3 toCamera = normalize(cameraPos - Pos);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(toCamera, up);



    Pos -= ( right * taille);
    Pos -= (0.5*taille); // pour centrer avec les lignes
    gl_Position = gVP * vec4(Pos, 1.0);
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    Pos.y += taille;
    gl_Position = gVP * vec4(Pos, 1.0);
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    Pos.y -= taille;
    Pos += (right * taille);
    gl_Position = gVP * vec4(Pos, 1.0);
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    Pos.y += taille;
    gl_Position = gVP * vec4(Pos, 1.0);
    fragColor = vec4(couleur.xyz, alpha);
    EmitVertex();

    EndPrimitive();


}
