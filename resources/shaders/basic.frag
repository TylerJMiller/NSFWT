#version 410
in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D Diffuse;
uniform sampler2D Normal;
uniform sampler2D Specular;

void main()
{
	FragColor = texture(Diffuse, vTexCoord);
	
	//BAD, PLS FIX
	//vec4 vdif = texture(Diffuse, vTexCoord);
	//vec4 vnor = texture(Normal, vTexCoord);
	//vec4 vspe = texture(Specular, vTexCoord);
	//FragColor = vdif + vnor * vspe;
}


