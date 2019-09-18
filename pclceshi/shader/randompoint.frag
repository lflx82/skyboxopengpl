#version 330 core

in vec2 textcoord;
in float dz;
out vec4 color;

uniform sampler2D frontDepthMap;
uniform sampler2D backDepthMap;

void main()
{	
	//color = vec4(1.0, 0.0, 1.0, 1.0f);
	float color1 = texture(backDepthMap, textcoord).r;
	float color2 = texture(frontDepthMap, textcoord).r;
	float color4=color1-color2;
	vec4 color3;
	//float dd=(gl_FragCoord.z+1.0)/2.0;
	float dd=dz;
	if (dd<color2) 
	{
	    if(color2-0.9999>0)
		{
			color3 = vec4(1.0,1.0,0.0,0.5);
		}
		else
		{
			color3 = vec4(1.0,0.0,0.0,0.5);
		}
	}
	else if(dd>color1)
    {
		color3 = vec4(0.0,1.0,0.0,0.3);
	}
	else
	{
		color3 = vec4(0.0,0.0,1.0,0.6);
	}
	 
	//color = vec4(color4,color4,color4,1.0);
	//color = vec4(dz,color1,color2,1.0);
	color =color3 ;
	//color = vec4(textcoord.x, textcoord.y, 0.0, 1.0);
}