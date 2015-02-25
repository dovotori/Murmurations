#version 330
layout(points) in;
layout(triangle_strip, max_vertices=6) out;

in vec4 geomColor[];

uniform mat4 view;
uniform mat4 projection;

out vec2 fragTexture;



void main()
{

	vec4 pos = gl_in[0].gl_Position;
    float profondeur = pos.z;
    float taille = 1.0 + (profondeur * 4.0);
    float alpha = 0.5 + (profondeur * 0.5);


    // 1EME TRIANGLE
    gl_Position = projection * view * pos;
    fragTexture = vec2(0.0, 0.0);
    EmitVertex();

    pos.x += taille;
    gl_Position = projection * view * pos;
    fragTexture = vec2(1.0, 0.0);
    EmitVertex();

    pos.y += taille;
    gl_Position = projection * view * pos;
    fragTexture = vec2(1.0, 1.0);
    EmitVertex();

    EndPrimitive();



    // 2EME TRIANGLE
    gl_Position = projection * view * pos;
    fragTexture = vec2(1.0, 1.0);
    EmitVertex();

    pos.x -= taille;
    gl_Position = projection * view * pos;
    fragTexture = vec2(0.0, 1.0);
    EmitVertex();

    pos.y -= taille;
    gl_Position = projection * view * pos;
    fragTexture = vec2(0.0, 0.0);
    EmitVertex();

    EndPrimitive();

}
