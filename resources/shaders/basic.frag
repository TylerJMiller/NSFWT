#version 410
in vec2 vTexCoord;
out vec4 FragColor;

uniform sampler2D Diffuse;

void main()
{
	FragColor = texture(Diffuse, vTexCoord);
	
	
}


