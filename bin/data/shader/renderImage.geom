#version 330
layout(points) in;
layout(triangle_strip, max_vertices=4) out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float tailleParticule;

out vec2 fragTexture;



void main()
{

	vec4 pos = gl_in[0].gl_Position;

    float profondeur = pos.z;
    float taille = (0.4 + (profondeur * 0.6)) * tailleParticule;

    pos.x -= 0.5; // -0.5 pour centrer  
    pos.y -= 0.5;
    pos.z -= 0.5;

    mat4 camera = projection * view;


    // 1EME TRIANGLE
    gl_Position = camera * pos;
    fragTexture = vec2(0.0, 0.0);
    EmitVertex();

    pos.x += taille;
    gl_Position = camera * pos;
    fragTexture = vec2(1.0, 0.0);
    EmitVertex();

    pos.x -= taille;
    pos.y += taille;
    gl_Position = camera * pos;
    fragTexture = vec2(0.0, 1.0);
    EmitVertex();

    pos.x += taille;
    gl_Position = camera * pos;
    fragTexture = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();


}
