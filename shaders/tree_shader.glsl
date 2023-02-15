#version 330
 
uniform sampler2D texture_2;
 
in vec2 texcoord;
 
layout(location = 0) out vec4 out_color;
 
void main()
{
	vec4 color = texture2D(texture_2, texcoord);         
	out_color = color;
}