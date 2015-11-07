#version 410
in vec2 vTexCoord;

in vec4 vNormal;
in vec4 vPosition;

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Specular;


layout(location = 0) out vec4 oAlbedo;
layout(location = 1) out vec4 oNormal;
layout(location = 2) out vec4 oPosition;


void main()
{
	//float d = max(0, dot( normalize(vNormal.xyz), vec3(0,1,0)));
	//FragColor = vec4(d,d,d,1);
	
	oAlbedo   = texture(Diffuse, vTexCoord); // albedo
	oPosition = vPosition;
	oNormal   = vNormal; 			
											 
											 
	//BAD, PLS FIX
	//vec4 vdif = texture(Diffuse, vTexCoord);
	//vec4 vnor = texture(Normal, vTexCoord);
	//vec4 vspe = texture(Specular, vTexCoord);
	//FragColor = vdif + vnor * vspe;
}


