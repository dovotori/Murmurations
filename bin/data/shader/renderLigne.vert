#version 330

in vec4 position;
in vec2 texcoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform sampler2D posTex;
uniform vec3 screen;
uniform float resolution;

out vec4 geomColor;
out float geomZ;

void main()
{
    vec2 st = texcoord / resolution;
    
    vec3 pixPos = texture(posTex, st).xyz;     // recupére position de la texture
    
    geomZ = pixPos.z;
    geomColor = vec4(1.0, 1.0, 1.0, 1.0);
    
    // map la position dans le nouvel espace
    pixPos.x = (pixPos.x * screen.x) - (screen.x / 2.0);
    pixPos.y = (pixPos.y * screen.y) - (screen.y / 2.0);
    pixPos.z = (pixPos.z * screen.z) - (screen.z / 2.0);
    
	gl_Position = projection * view * model * vec4(pixPos, 1.0);

}

