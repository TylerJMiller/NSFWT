#version 410
in vec2 vTexCoord;
out vec4 FragColor;
in float Depth;

uniform sampler2D Diffuse;
void main()
{
	//FragColor = normalize(vec4(1,1,1,1) * texture(Diffuse, vTexCoord));
	//FragColor = vec4(gl_FragCoord.z);
	
	FragColor = vec4(1,1,1,0) - vec4(Depth, Depth, Depth, 0);
}


