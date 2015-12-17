#version 410
//in vec2 vTexCoord;
//out vec4 FragColor;
//in float Depth;

//uniform sampler2D Diffuse;

out vec4 FragDepth;

void main()
{
	FragDepth = vec4(gl_FragCoord.zzz,1);
	//FragColor = texture(Diffuse, vTexCoord);
	
	//depth
//	FragColor = vec4(1,1,1,0) - vec4(Depth, Depth, Depth, 0);
}