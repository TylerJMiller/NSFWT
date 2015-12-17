#version 410
in vec2 vTexCoord;
in vec4 vDirection;

out vec4 FragColor;

uniform vec4 Color;

uniform sampler2D Normal; // GPass Normals
uniform sampler2D Position; // GPass Normals
uniform sampler2D Shadow; // GPass Normals

uniform mat4 View;

uniform mat4 LightProjection;
uniform mat4 LightView;
uniform mat4 texSpaceOffset ;

void main()
{
	vec4 normal 	= texture(Normal, vTexCoord.xy);
	vec4 position 	= texture(Position, vTexCoord.xy);

	// shadowCoord isn't sampling correctly
	//vec4 shadowCoord = textureSpaceOffset  * LightProjection * LightView * inverse(View) * position; // into worldspace
	
	mat4 lightViewProjection = texSpaceOffset * LightProjection * LightView;

	vec4 shadowCoord = lightViewProjection * inverse(View) * position;
	
	float d = max(0, dot(normal, vDirection));
	
	float visibility = 1.f;
	
	vec4 shadowMap = texture(Shadow, shadowCoord.xy);
	
	if(shadowMap.z < shadowCoord.z)
	{
		visibility = step(shadowMap.x, .01f);
	}

	FragColor = d * (Color + visibility);
	//FragColor = texture(Normal, vTexCoord.xy);
	
	
	//FragColor = vec4(shadowCoord.xyz,1);
	//FragColor = shadowMap;
	//FragColor = texture(Shadow, vTexCoord.xy); // FBOs are okay,
	//FragColor = shadowCoord;
	//FragColor = vec4(texture(Shadow,shadowCoord.xy).zzz,1);
}

/*
	Take the position and move it into light space

*/