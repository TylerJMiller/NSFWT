#version 410
in vec2 vTexCoord;

out vec4 FragColor;

in vec4 vDirection;
uniform vec4 Color;

uniform sampler2D Normal; // GPass Normals
uniform sampler2D Position; // GPass Normals
uniform sampler2D Shadow; // GPass Normals

uniform mat4 LightProjection;
uniform mat4 LightView;

uniform mat4 View;

uniform mat4 clipToUV = mat4(.5f,  0 ,  0,   0,
							  0,  .5f,  0,   0,
							  0,   0,  .5f,  0,
							 .5f, .5f, .5f,  1.f);


void main()
{
	vec4 normal 	= texture(Normal, vTexCoord.xy);
	vec4 position 	= vec4(texture(Position, vTexCoord.xy).xyz,1);

	vec4 shadowCoord = clipToUV * LightProjection * LightView * inverse(View) * position; // into worldspace
	
	float visibility = 1.f;
	
	
	if(texture(Shadow,shadowCoord.xy).z < shadowCoord.z)
	{
		visibility = 0;
	}
	
	float d = max(0, dot(normal, vDirection));

	FragColor = visibility*d*Color;
	
	//FragColor = shadowCoord;
	//FragColor = vec4(texture(Shadow,shadowCoord.xy).zzz,1);
	}


/*
	Take the position and move it into light space

*/