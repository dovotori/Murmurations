#version 330
layout(points) in;
layout(triangle_strip, max_vertices=33) out;

in vec4 geomColor[];
in float geomZ[];
in float geomAngle[];

out vec4 fragColor;


float map(float valeur, float minRef, float maxRef, float minDest, float maxDest)
{
    return minDest + (valeur - minRef) * (maxDest - minDest) / (maxRef - minRef);
}



void main()
{
    float angle = 1.0; //geomAngle[0];

    float M_PI = 3.141592653589793238462643383279502884;
    float taille = 20.0 + (geomZ[0] * 100.0);
    int details = 10;
    float alpha = 0.5 + (geomZ[0] * 0.5);

    vec4 pos = gl_in[0].gl_Position;

    int i;
    for (i = 0; i < details; i++) {

        gl_Position = pos;
        fragColor = vec4(geomColor[0].xyz, 1.0);
        EmitVertex();

        float angle = map(i, 0, details, angle, angle+(M_PI*2));
        float x = (cos(angle) * taille * 0.2);
        float y = (sin(angle) * taille);
        gl_Position = vec4(pos.x+x, pos.y+y, pos.z, 1.0);
        fragColor = vec4(geomColor[0].xyz, 1.0);
        EmitVertex();

        angle = map(i+1, 0, details, angle, angle+(M_PI*2));
        x = (cos(angle) * taille  * 0.2);
        y = (sin(angle) * taille);
        gl_Position = vec4(pos.x+x, pos.y+y, pos.z, 1.0);
        fragColor = vec4(geomColor[0].xyz, 1.0);
        EmitVertex();

        EndPrimitive();
    }

}
