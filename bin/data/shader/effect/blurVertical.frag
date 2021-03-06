#version 330

in vec2 fragTexture;

uniform vec2 resolution;
uniform sampler2D fboTexture;
uniform float blurness;

out vec4 outputColor;



vec4 blurV(vec2 st)
{
   vec4 color = vec4(0.0);

   float blur = blurness / resolution.y;
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   color += texture(fboTexture, vec2(st.x, st.y - 4.0*blur)) * 0.05;
   color += texture(fboTexture, vec2(st.x, st.y - 3.0*blur)) * 0.09;
   color += texture(fboTexture, vec2(st.x, st.y - 2.0*blur)) * 0.12;
   color += texture(fboTexture, vec2(st.x, st.y - blur)) * 0.15;
   color += texture(fboTexture, vec2(st.x, st.y)) * 0.16;
   color += texture(fboTexture, vec2(st.x, st.y + blur)) * 0.15;
   color += texture(fboTexture, vec2(st.x, st.y + 2.0*blur)) * 0.12;
   color += texture(fboTexture, vec2(st.x, st.y + 3.0*blur)) * 0.09;
   color += texture(fboTexture, vec2(st.x, st.y + 4.0*blur)) * 0.05;
 
   return color;
}



void main() {
   
   vec2 st = fragTexture * resolution; // map les coor de 0,1 à 0,taille de texture
   vec4 color = blurV(st); 
   outputColor = color; 

}


