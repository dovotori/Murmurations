#version 330
layout(points) in; layout(points, max_vertices=1) out;

uniform mat4 view;
uniform mat4 projection;
uniform vec3 screen;
uniform vec3 couleur;

out vec4 fragColor;



void main()
{
	vec4 pos = gl_in[0].gl_Position; // va de 0 à 1
    float alpha = 0.4 + (pos.z * 0.6); 

    // map la position dans le nouvel espace
    pos.x = (pos.x * screen.x) - (screen.x / 2.0);
    pos.y = (pos.y * screen.y) - (screen.y / 2.0);
    pos.z = (pos.z * screen.z) - (screen.z / 2.0);

    gl_Position = projection * view * pos;
    fragColor = vec4(couleur, alpha);
    EmitVertex();

    EndPrimitive();

}
