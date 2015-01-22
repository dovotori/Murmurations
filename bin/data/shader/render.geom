#version 330 
layout(points) in;
layout(triangle_strip, max_vertices=3) out;

in vec4 geomColor[];
in float geomZ[];
out vec4 fragColor;






void main()
{   
	vec4 pos = gl_in[0].gl_Position;

    fragColor = geomColor[0] * geomZ[0];
    fragColor.a = 1.0;

    float taille = 0.2 + (geomZ[0] * 4.0);

    
    gl_Position = pos;
    EmitVertex();

    pos.x += taille;
    gl_Position = pos;
    EmitVertex();

    pos.y += taille;
    gl_Position = pos;
    EmitVertex();

    EndPrimitive();



}