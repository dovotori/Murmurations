#version 330 
layout(points) in;
layout(triangle_strip, max_vertices=3) out;

in vec4 geomColor[];
in float geomZ[];

out vec4 fragColor;



void main()
{

	vec4 pos = gl_in[0].gl_Position;
    //float taille = 0.2 + (geomZ[0] * 4.0);
    float taille = 1.2;

    
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, 1.0);
    EmitVertex();

    pos.x += taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, 1.0);
    EmitVertex();

    pos.y += taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, 1.0);
    EmitVertex();

    EndPrimitive();

}