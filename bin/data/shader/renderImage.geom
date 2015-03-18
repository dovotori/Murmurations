#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

in vec3 geomVel[];

uniform mat4 view;
uniform mat4 projection;
uniform vec4 couleur;
uniform vec3 cameraPos;
uniform float tailleParticule;

out vec2 fragTexture;
out vec4 fragColor;


void main()
{
	vec4 pos = gl_in[0].gl_Position;

    float profondeur = pos.z;
    float taille = (0.4 + (profondeur * profondeur * 2.6)) * tailleParticule;
    float alpha = couleur.a;

    // SPRITE
    float spriteColonne = 0.5;
    vec2 spriteOffset = vec2(0.0, 0.0);
    if(profondeur < 0.1) { spriteOffset = vec2(0.0, 0.0);} // tres loin
    else if(profondeur < 0.3) { spriteOffset = vec2(1.0, 0.0); } // loin
    else if(profondeur < 0.5) { spriteOffset = vec2(0.0, 1.0); } // moyen loin
    else if(profondeur < 0.6) { spriteOffset = vec2(1.0, 1.0); } // moyen
    else if(profondeur < 0.7) { spriteOffset = vec2(0.0, 1.0); } // moyen proche
    else if(profondeur < 0.9) { spriteOffset = vec2(1.0, 0.0); } // proche 
    else { spriteOffset = vec2(0.0, 0.0); } // tres proche 

    pos.xyz -= 0.5; // -0.5 pour centrer dans l'ecran

    // COULEUR DIFFUSE
    vec3 rayon = normalize(vec3(1.0) - pos.xyz);
    vec3 mapVel = (geomVel[0] + 1.0) * 0.5;
    float angle = max(dot(normalize(mapVel), rayon), 0.0);

    // ROTATION
    mat4 gVP = projection * view;
    vec3 Pos = pos.xyz;
    vec3 toCamera = normalize(cameraPos - Pos);
    vec3 up = vec3(0.0, 1.0, 0.0);
    vec3 right = cross(toCamera, up);

    // DESSIN
    Pos -= (right * taille);
    Pos -= (0.5*taille); // pour centrer avec les lignes
    gl_Position = gVP * vec4(Pos, 1.0);
    fragTexture = vec2(0.0, 0.0) * spriteColonne + (spriteOffset * spriteColonne);
    fragColor = vec4(couleur.xyz * angle, alpha);
    EmitVertex();

    Pos.y += taille;
    gl_Position = gVP * vec4(Pos, 1.0);
    fragTexture = vec2(0.0, 1.0) * spriteColonne + (spriteOffset * spriteColonne);
    fragColor = vec4(couleur.xyz * angle, alpha);
    EmitVertex();

    Pos.y -= taille;
    Pos += (right * taille);
    gl_Position = gVP * vec4(Pos, 1.0);
    fragTexture = vec2(1.0, 0.0) * spriteColonne + (spriteOffset * spriteColonne);
    fragColor = vec4(couleur.xyz * angle, alpha);
    EmitVertex();

    Pos.y += taille;
    gl_Position = gVP * vec4(Pos, 1.0);
    fragTexture = vec2(1.0, 1.0) * spriteColonne + (spriteOffset * spriteColonne);
    fragColor = vec4(couleur.xyz * angle, alpha);
    EmitVertex();

    EndPrimitive();


}
