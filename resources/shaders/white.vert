#version 410
layout (location = 0) in vec4 Position;
layout (location = 3) in vec2 TexCoord;

out vec2 vTexCoord;

out float Depth;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;
uniform float cPosx;
uniform float cPosy;
uniform float cPosz;
uniform float Fard;

void main()
{
	vTexCoord = TexCoord;

	gl_Position = Projection * View * Model * Position;
	Depth = distance(vec3(cPosx, cPosy,cPosz),vec3(gl_Position.x,gl_Position.y,gl_Position.z)) / Fard;
}