#version 330 
layout(triangles) in;
layout(line_strip, max_vertices=3) out;

in vec4 geomColor[];
in float geomZ[];

out vec4 fragColor;

void main()
{	
  for(int i=0; i<3; i++)
  {
    gl_Position = gl_in[i].gl_Position;
    fragColor = vec4(geomColor[i].xyz * geomZ[i], 1.0);
    EmitVertex();
  }
  EndPrimitive();
}  