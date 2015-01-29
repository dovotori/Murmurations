#version 330 
layout(lines) in;
layout(line_strip, max_vertices=2) out;

in vec4 geomColor[];
in float geomZ[];

out vec4 fragColor;

void main()
{	
    /*for(int i=0; i<gl_in.length(); i++)
   {
    gl_Position = gl_in[i].gl_Position;
    fragColor = vec4(geomColor[i].xyz * geomZ[i], 1.0);
    EmitVertex();
   }*/

    gl_Position = gl_in[0].gl_Position;
    fragColor = vec4(geomColor[0].xyz * geomZ[0], 1.0);
    EmitVertex();
    
    gl_Position = gl_in[1].gl_Position;
    fragColor = vec4(geomColor[1].xyz * geomZ[1], 1.0);
    EmitVertex();
    
    EndPrimitive();
}  