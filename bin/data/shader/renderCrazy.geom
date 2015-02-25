#version 330
layout(points) in;
layout(triangle_strip, max_vertices=6) out;

in vec4 geomColor[];

uniform mat4 view;
uniform mat4 projection;

out vec4 fragColor;



float random(vec2 scale, float seed, vec2 variations) {
    // entre 0 et 1
    return fract( sin( dot( variations + seed, scale ) ) * 43758.5453 + seed );
}


void main()
{

	vec4 pos = gl_in[0].gl_Position;
    float profondeur = pos.z;
    float taille = 1.0 + (profondeur * 4.0);
    float alpha = 0.5 + (profondeur * 0.5);


    int i, j;
    for(j = 0; j < 2; j++)
    {
        for(i = 0; i < 3; i++)
        {
            float r = random( vec2( 1.0 ), length( vec2(pos.x, pos.y) ), vec2(pos.x, pos.y) );
            r = (r * 2.0) - 1.0;

            if(i == 1){ pos.x += taille * r; }
            if(i == 2){ pos.y += taille * r; }

            gl_Position = projection * view * pos;
            fragColor = vec4(geomColor[0].xyz, alpha);
            EmitVertex();
        }
        EndPrimitive();
    }


}
