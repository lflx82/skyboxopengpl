#version 330 core

in  vec4 col;
in  vec2 text;
uniform sampler2D texture;
uniform float w;

out vec4 color;

void main()
{	
   //color=col;
    color= texture2D(texture, text);
    color.w=w;
}