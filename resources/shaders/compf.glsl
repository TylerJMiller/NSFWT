#version 410
in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D Albedo;
uniform sampler2D LightColor;


void main()
{
	FragColor = texture(Albedo, vTexCoord) * texture(LightColor,vTexCoord);
}