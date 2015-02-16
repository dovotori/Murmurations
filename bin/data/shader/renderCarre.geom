#version 330
layout(points) in;
layout(triangle_strip, max_vertices=6) out;

in vec4 geomColor[];
in float geomZ[];

out vec4 fragColor;



void main()
{

	vec4 pos = gl_in[0].gl_Position;
    float taille = 1.0 + (geomZ[0] * 4.0);
    float alpha = 0.5 + (geomZ[0] * 0.5);

    // 1EME TRIANGLE
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    pos.x += taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    pos.y += taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    EndPrimitive();



    // 2EME TRIANGLE
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    pos.x -= taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    pos.y -= taille;
    gl_Position = pos;
    fragColor = vec4(geomColor[0].xyz, alpha);
    EmitVertex();

    EndPrimitive();

}
