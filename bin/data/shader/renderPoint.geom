#version 330
layout(points) in;
layout(points, max_vertices=1) out;

in vec4 geomColor[];
in float geomZ[];

out vec4 fragColor;



void main()
{
    float alpha = 0.5 + (geomZ[0] * 0.5);

    gl_Position = gl_in[0].gl_Position;
    fragColor = vec4(geomColor[0].xyz * geomZ[0], alpha);
    EmitVertex();

    EndPrimitive();

}
