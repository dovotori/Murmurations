#version 330
uniform mat4 model; uniform mat4 view; uniform mat4 projection;
in vec4 position; in vec4 color;
out vec4 fragColor;
void main(){ fragColor = color; gl_Position = projection * view * model * position; }